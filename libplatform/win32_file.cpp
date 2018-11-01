#include "file.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


// A lot of the windows code can only deal with DWORDs (unsigned 32 bit int)
// when it comes to reading and writing data or converting utf8 / utf16 strings.
// I don't expect this will ever be a problem as I don't see myself writing
// code to read or write 4 gigs in one hit.

namespace platform {

class file_private {
public:
	file_private()
		:fp(INVALID_HANDLE_VALUE),is_error(false)
	{}
	~file_private() {
		if(fp != INVALID_HANDLE_VALUE){
			CloseHandle(fp);
		}
	}

	HANDLE fp;
	bool is_error;
};

}

platform::file::file()
	:m_data(new file_private)
{
}

platform::file::file(const platform::char_t *filename, io_mode iomode, create_mode cmode)
	:file()
{
	open(filename, iomode, cmode);
}

platform::file::file(const platform::string_t &filename, io_mode iomode, create_mode cmode)
	: file()
{
	open(filename, iomode, cmode);
}

platform::file::~file()
{
}

bool platform::file::open(const platform::string_t &filename, io_mode iomode, create_mode cmode)
{
	return open(filename.c_str(), iomode, cmode);
}

bool platform::file::open(const platform::char_t *filename, io_mode iomode, create_mode cmode)
{
	DWORD access = 0;
	DWORD disposition = 0;

	switch(iomode) {
	case io_mode::read:
		access = GENERIC_READ;
		break;
	case io_mode::write:
		access = GENERIC_WRITE;
		break;
	case io_mode::readwrite:
		access = GENERIC_READ | GENERIC_WRITE;
		break;
	}

	switch(cmode){
	case create_mode::open:
		disposition = OPEN_ALWAYS;
		break;
	case create_mode::exist:
		disposition = OPEN_EXISTING;
		break;
	case create_mode::create:
		disposition = CREATE_NEW;
		break;
	case create_mode::trunc:
		disposition = CREATE_ALWAYS;
		break;
	}

	m_data->fp = CreateFile(
		filename,
		access, // dwDesiredAccess
		0, // dwShareMode
		NULL, // lpSecurityAttributes
		disposition,  // dwCreationDisposition
		FILE_ATTRIBUTE_NORMAL, // dwFlagsAndAttributes
		NULL // hTemplateFile
	);

	if(m_data->fp == INVALID_HANDLE_VALUE){
		return false;
	}

	return true;
}

bool platform::file::is_open()
{
	return m_data->fp != INVALID_HANDLE_VALUE;
}

void platform::file::close()
{
	if(m_data->fp != INVALID_HANDLE_VALUE){
		CloseHandle(m_data->fp);
		m_data->fp = INVALID_HANDLE_VALUE;
	}
}

size_t platform::file::tell()
{
	LARGE_INTEGER to_move;
	LARGE_INTEGER location;

	to_move.QuadPart = 0;

	DWORD rc = SetFilePointerEx(m_data->fp, to_move, &location, FILE_CURRENT);

	return location.QuadPart;
}

size_t platform::file::length()
{
	LARGE_INTEGER size;

	if(GetFileSizeEx(m_data->fp, &size)){
		return size.QuadPart;
	}

	return 0;
}

void platform::file::flush()
{
	FlushFileBuffers(m_data->fp);
}

void platform::file::truncate()
{
	seek(0, platform::file::seek_dir::beg);
	SetEndOfFile(m_data->fp);
}

void platform::file::trim()
{
	SetEndOfFile(m_data->fp);
}

size_t platform::file::seek(int64_t offset, platform::file::seek_dir seek_direction)
{
	BOOL rc;
	DWORD method;
	LARGE_INTEGER size;
	LARGE_INTEGER location;

	switch(seek_direction){
	case file::seek_dir::beg:
		method = FILE_BEGIN;
		break;
	case file::seek_dir::end:
		method = FILE_END;
		break;
	case file::seek_dir::cur:
		method = FILE_CURRENT;
		break;
	}

	size.QuadPart = offset;

	rc = SetFilePointerEx(m_data->fp, size, &location, method);

	if(!rc){
		// error
	}

	return location.QuadPart;
}

size_t platform::file::write_utf8(const platform::string_t &data)
{
	return write_utf8(data.c_str(), data.length());
}

size_t platform::file::write_utf8(const platform::char_t *data, size_t length)
{
	if constexpr (sizeof(char) == sizeof(platform::char_t)){
		BOOL rc = FALSE;
		DWORD written = 0;
		// UTF 8 strings
		rc = WriteFile(m_data->fp, data, static_cast<DWORD>(length), &written, NULL);
		return written;
	}
	else if constexpr(sizeof(wchar_t) == sizeof(platform::char_t)){
		// UTF-16 codepath.  Convert to UTF and write out to disk.
		DWORD written = 0;

		const int bufsize = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS,
			data, static_cast<DWORD>(length),
			NULL, 0,
			NULL, NULL);

		if(bufsize == 0){
			return 0;
		}

		auto buffer = std::make_unique<char[]>(bufsize);

		const int converted = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS,
			data, static_cast<DWORD>(length),
			buffer.get(), static_cast<DWORD>(bufsize),
			NULL, NULL);

		WriteFile(m_data->fp, buffer.get(), static_cast<DWORD>(converted), &written, NULL);

		return written;
	}

	return 0;
}

size_t platform::file::read_utf8(platform::string_t &data)
{
	if constexpr (sizeof(char) == sizeof(platform::char_t)){
		auto file_length = length();
		if(file_length == 0){
			return 0;
		}

		DWORD bytes_read = 0;
		data.clear();
		data.resize(file_length);

		BOOL rc = ReadFile(m_data->fp, data.data(), static_cast<DWORD>(file_length), &bytes_read, NULL);
		if(!rc){
			return 0;
		}

		return bytes_read;
	}
	else if constexpr (sizeof(wchar_t) == sizeof(platform::char_t)) {
		DWORD bytes_read;
		BOOL rc;
		const size_t fp_where = tell();
		const size_t fp_len = length();

		const size_t to_read = fp_len - fp_where;

		auto buffer = std::make_unique<char[]>(to_read);

		rc = ReadFile(m_data->fp, buffer.get(), static_cast<DWORD>(to_read), &bytes_read, NULL);
		if(!rc){
			return 0;
		}

		const int sz = MultiByteToWideChar(
			CP_UTF8, MB_ERR_INVALID_CHARS,
			buffer.get(), bytes_read,
			NULL, 0);

		if(sz == 0){
			return 0;
		}

		data.clear();
		data.resize(sz, '\0' );

		const int written = MultiByteToWideChar(
			CP_UTF8, MB_ERR_INVALID_CHARS,
			buffer.get(), bytes_read,
			data.data(), sz);

		return bytes_read;
	}
}

size_t platform::file::write(const char *data, size_t length)
{
	DWORD written = 0;

	BOOL rc = WriteFile(m_data->fp, data, static_cast<DWORD>(length), &written, NULL);

	return written;
}

size_t platform::file::read(char *data, size_t length)
{
	DWORD read = 0;
	BOOL rc = ReadFile(m_data->fp, data, static_cast<DWORD>(length), &read, NULL);

	return read;
}
