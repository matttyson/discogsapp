#pragma once

#include <memory>
#include "platform.hpp"

/*
	A class to abstract away native platform file IO.

	methods will return -1 or false on any error.
	call last_error() to get an error code (note,
	most error codes aren't implemented yet)

	This class has the ability to write platform::string_t
	types out to disk as utf8 strings and read in utf8
	strings and convert them to a platform::string_t (which
	may or may not be a utf16 string).

	TODO: Implement routines for writing out fundamental types
	and byte swapping if I ever need binary I/O.

	TODO: Reading in utf8 strings is an issue if we want to
	limit the length.  Do we limit it by bytes or code points?
	bytes is simple but requires the user to know in advance
	how many code points there are.

	doing it by code points means the read routine has to
	inspect the utf8 data as it comes in which complicates the
	routine a bit.
*/

namespace platform {

class file_private;

class file {
public:

	enum class seek_dir {
		beg, // seek from beginning of file
		end, // seek from end of file
		cur  // seek from current location
	};

	enum class io_mode {
		read,       // read only
		write,      // write only
		readwrite   // read-write
	};

	enum class create_mode {
		open,   // if exists, open.     if not, create.
		exist,  // if exists, open.     if not, error.
		create, // if exists, error.    if not, create.
		trunc,  // if exists, truncate. if not, create.
	};

	enum class error {
		success,          // no error.
		file_exists,      // the file already exists.
		file_not_exists,  // the file does not exist.
		file_closed,      // the file is closed.
		file_read_only,   // the file is opened in read only mode.
		file_write_only,  // the file is opened in write only mode.
		access_denied,    // access to the file was denied.
		unknown,
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

	error last_error()const;

	// Close the file.  Will be done automatically on object destruction.
	void close();

	// True if the file is open, False if not.
	bool is_open();

	// Set the file to empty with a length of zero bytes.
	bool truncate();

	// Set the current file pointer location to be the end of the file.
	bool trim();

	// Call the underlying operating system flush routine.
	bool flush();

	// Current position in file.
	int64_t tell();

	// File length.
	int64_t length();

	// See within the file.  Returns new file pointer position.
	int64_t seek(int64_t offset, seek_dir seek_direction);

	// Writes text out as UTF8 data. Returns the number of bytes written.
	// Note that this function converts 'data' to UTF8 if it is not already.
	// The number of bytes written to disk may not be the same as 'data';
	int64_t write_utf8(const platform::string_t &data);
	int64_t write_utf8(const platform::char_t *data, size_t length);

	// Read text in as UTF8 and convert it to platform UTF if needed.
	// Note, this will slurp the whole file into memory.
	// Slurps from the current location to the end of the file.

	// Returns the number of bytes read from disk.  This may not be the
	// same as the number of characters in 'data'.
	int64_t read_utf8(platform::string_t &data);

	// Write 'length' bytes from 'data' out to disk.
	// Returns the number of bytes written.
	int64_t write(const char *data, size_t length);

	// Read read 'length' bytes from disk into 'data'
	// Returns the number of bytes read.
	int64_t read(char *data, size_t length);

private:
	std::unique_ptr<file_private> m_data;
};

}
