#pragma once

#include <memory>
#include "platform.hpp"

namespace platform {

class file_private;

class file {
public:

	enum class seek_dir {
		beg, // seek from beginning
		end, // seek from end
		cur  // seek from current location
	};

	enum class io_mode {
		read,       // read only
		write,      // write only
		readwrite   // read-write
	};

	enum class create_mode {
		open,   // if exist, open. if not, create.
		exist,  // if exists, open, if not, error.
		create, // if exists, error. if not, create.
		trunc,  // if exists, truncate.  if not, create.
	};

public:
	file();

	file(const file &) = delete;
	file& operator=(const file &) = delete;
	file(file &&) noexcept = delete;
	file& operator=(file &&) = delete;

	file(const platform::char_t *filename, io_mode iomode, create_mode cmode);
	file(const platform::string_t &filename, io_mode iomode, create_mode cmode);
	~file();

	bool open(const platform::char_t *filename, io_mode iomode, create_mode cmode);
	bool open(const platform::string_t &filename, io_mode iomode, create_mode cmode);
	void close();

	// True if the file is open
	bool is_open();

	// Set the file to empty with a length of zero bytes
	void truncate();

	// Set the current file pointer location to be the end of the file
	void trim();

	// Flush the buffers to disk
	void flush();

	// Current position in file.
	size_t tell();

	// File length.
	size_t length();

	// See within the file.
	size_t seek(int64_t offset, seek_dir seek_direction);

	// Writes text out as UTF8 data.
	size_t write_utf8(const platform::string_t &data);
	size_t write_utf8(const platform::char_t *data, size_t length);

	// Read text in as UTF8 and convert it to platform UTF if needed.
	// Note, this will slurp the whole file into memory.
	// Slurps from the current location to the end of the file.
	size_t read_utf8(platform::string_t &data);

	// Write some bytes of data out to disk.
	size_t write(const char *data, size_t length);

	// Read some random bits of data from disk
	size_t read(char *data, size_t length);

private:
	std::unique_ptr<file_private> m_data;
};

}
