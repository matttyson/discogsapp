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
	file_private():fd(-1),errcode(file::error::unknown){}
	~file_private(){
		if(fd != -1){
			::close(fd);
		}
	}

	void clear_error() {
		errcode = file::error::success;
	}

	void set_error() {
		switch(errno){
		case EACCES:
			errcode = file::error::access_denied;
			break;
		case EEXIST:
			errcode = file::error::file_exists;
			break;
		case ENOENT:
			errcode = file::error::file_not_exists;
			break;
		default:
			errcode = file::error::unknown;
		}
	}

	int fd;
	file::error errcode;
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
		m_data->set_error();
		return false;
	}

	m_data->fd = fd;
	m_data->clear_error();

	return true;
}

platform::file::error platform::file::last_error()const
{
	return m_data->errcode;
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

bool platform::file::truncate()
{
	seek(0, seek_dir::beg);
	const int rc = ftruncate(m_data->fd, 0);
	if (rc == -1) {
		m_data->set_error();
		return false;
	}
	m_data->clear_error();
	return true;
}

bool platform::file::trim()
{
	const size_t location = tell();
	const int rc = ftruncate(m_data->fd, location);
	if (rc == -1) {
		m_data->set_error();
		return false;
	}
	m_data->clear_error();
	return true;
}

bool platform::file::flush()
{
	const int rc = fsync(m_data->fd);
	if (rc == -1) {
		m_data->set_error();
		return false;
	}
	m_data->clear_error();
	return true;

}

int64_t platform::file::tell()
{
	const off_t location = lseek64(m_data->fd, 0, SEEK_CUR);
	if(location == -1){
		m_data->set_error();
		return -1;
	}
	m_data->clear_error();
	return location;
}

int64_t platform::file::length()
{
	const int64_t location = tell();
	const off_t end = lseek(m_data->fd, 0, SEEK_END);
	if(end == -1){
		m_data->set_error();
		return -1;
	}

	const int rc = lseek64(m_data->fd, location, SEEK_SET);
	if(rc == -1){
		m_data->set_error();
		return -1;
	}

	m_data->clear_error();
	return end;
}

int64_t platform::file::seek(int64_t offset, seek_dir seek_direction)
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

	const off64_t rc = lseek64(m_data->fd, offset, whence);
	if(rc == -1){
		m_data->set_error();
		return -1;
	}
	return rc;
}

int64_t platform::file::write_utf8(const platform::string_t &data)
{
	return write_utf8(data.c_str(), data.length());
}

int64_t platform::file::write_utf8(const platform::char_t *data, size_t length)
{
	const ssize_t rc = ::write(m_data->fd, data, length);

	if(rc >= 0){
		return rc;
	}
	m_data->set_error();
	return -1;
}

int64_t platform::file::read_utf8(platform::string_t &data)
{
	const int64_t filesz = length();

	data.clear();
	data.resize(filesz);

	const ssize_t bytes_read = ::read(m_data->fd, data.data(), filesz);

	if(bytes_read > 0){
		if (bytes_read > 0 && bytes_read != filesz) {
			data.resize(bytes_read);
		}

		m_data->clear_error();
		return bytes_read;
	}
	else if (bytes_read == 0) {
		m_data->clear_error();
		return bytes_read;
	}
	else {
		m_data->set_error();
		return -1;
	}
}

int64_t platform::file::write(const char *data, size_t length)
{
	const ssize_t rc = ::write(m_data->fd, data, length);

	if(rc >= 0){
		m_data->clear_error();
		return rc;
	}

	m_data->set_error();

	return -1;
}

int64_t platform::file::read(char *data, size_t length)
{
	const ssize_t bytes_read = ::read(m_data->fd, data, length);

	if(bytes_read > 0){
		m_data->clear_error();
		return bytes_read;
	}

	m_data->set_error();

	return -1;
}
