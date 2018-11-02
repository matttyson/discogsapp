#include "file.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Note: The linux implementaton only deals with char and not wchar_t
static_assert(sizeof(char) == sizeof(platform::char_t));

namespace platform {
class file_private {
public:
	file_private():fd(-1){}
	~file_private(){
		if(fd != -1){
			::close(fd);
		}
	}

	int fd;
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

bool platform::file::open(const platform::char_t *filename, io_mode iomode, create_mode cmode)
{
	int flags = 0;


	switch (iomode) {
	case io_mode::read:
		flags |= O_RDONLY;
		break;
	case io_mode::write:
		flags |= O_WRONLY;
		break;
	case io_mode::readwrite:
		flags |= O_WRONLY;
		break;
	}

	switch (cmode) {
	case create_mode::open:
		flags |= O_CREAT;
		break;
	case create_mode::exist:
		break;
	case create_mode::create:
		flags |= O_CREAT | O_EXCL;
		break;
	case create_mode::trunc:
		flags |= O_CREAT | O_TRUNC;
		break;
	}

	const int fd = ::open(filename, flags);

	if(fd == -1){
		const int errsv = errno;
		return false;
	}

	m_data->fd = fd;

	return true;
}

bool platform::file::open(const platform::string_t &filename, io_mode iomode, create_mode cmode)
{
	return open(filename.c_str(), iomode, cmode);
}

void platform::file::close()
{
	if(m_data->fd != -1){
		::close(m_data->fd);
		m_data->fd = -1;
	}
}

bool platform::file::is_open()
{
	return m_data->fd != -1;
}

void platform::file::truncate()
{
	ftruncate(m_data->fd, 0);
}

void platform::file::trim()
{
	const size_t location = tell();
	ftruncate(m_data->fd, location);
}

void platform::file::flush()
{
	fsync(m_data->fd);
}

size_t platform::file::tell()
{
	const off_t location = lseek(m_data->fd, 0, SEEK_CUR);
	return location;
}

size_t platform::file::length()
{
	const size_t location = tell();
	const off_t end = lseek(m_data->fd, 0, SEEK_END);

	lseek(m_data->fd, location, SEEK_SET);

	return end;
}

size_t platform::file::seek(int64_t offset, seek_dir seek_direction)
{
	int whence = 0;

	switch(seek_direction){
	case seek_dir::beg:
		whence = SEEK_SET;
		break;
	case seek_dir::end:
		whence = SEEK_END;
		break;
	case seek_dir::cur:
		whence = SEEK_CUR;
		break;
	}

	lseek64(m_data->fd, offset, whence);
}

size_t platform::file::write_utf8(const platform::string_t &data)
{
	return write_utf8(data.c_str(), data.length());
}

size_t platform::file::write_utf8(const platform::char_t *data, size_t length)
{
	const ssize_t rc = ::write(m_data->fd, data, length);

	if(rc >= 0){
		return rc;
	}

	int errsv = errno;
}

size_t platform::file::read_utf8(platform::string_t &data)
{
	const size_t filesz = length();

	data.clear();
	data.resize(filesz);

	const ssize_t bytes_read = ::read(m_data->fd, data.data(), filesz);

	if(bytes_read > 0){
		if (bytes_read > 0 && bytes_read != filesz) {
			data.resize(bytes_read);
		}

		return bytes_read;
	}

	const int errsv = errno;

	return 0;
}

size_t platform::file::write(const char *data, size_t length)
{
	const ssize_t rc = ::write(m_data->fd, data, length);

	if(rc >= 0){
		return rc;
	}

	const int errsv = errno;

	return 0;
}

size_t platform::file::read(char *data, size_t length)
{
	const ssize_t bytes_read = ::read(m_data->fd, data, length);

	if(bytes_read > 0){
		return bytes_read;
	}

	const int errsv = errno;

	return 0;
}
