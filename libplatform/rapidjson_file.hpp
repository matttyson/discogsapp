#include "file.hpp"
#include <memory>

// RapidJSON file reader and writer classes

namespace platform {

class PlatformWriteStream {
public:
	typedef char Ch;

	PlatformWriteStream(
		platform::file &file_,
		char *buffer_,
		size_t buffer_size_
	)
	:buffer(buffer_), buffer_size(buffer_size_),
		count(0),file(file_)
	{}

	PlatformWriteStream(const PlatformWriteStream&) = delete;
	PlatformWriteStream& operator=(const PlatformWriteStream&) = delete;
	PlatformWriteStream(PlatformWriteStream&&)noexcept = delete;
	PlatformWriteStream& operator=(PlatformWriteStream&&)noexcept = delete;


	void Put(Ch c) {
		if(count == buffer_size){
			Flush();
		}
		buffer[count++] = c;
	}

	void Flush() {
		if(count > 0){
			file.write(buffer, count);
			count = 0;
		}
	}

private:
	char *buffer;
	size_t buffer_size;
	size_t count;
	platform::file &file;
};

class PlatformReadStream {
public:
	typedef char Ch;
	PlatformReadStream(
		platform::file &file_,
		char *buffer_,
		size_t buffer_size_
	)
	:buffer(buffer_),
		buffer_start(buffer_),
		buffer_end(buffer_),
		buffer_size(buffer_size_),
		bytes_read(0),
		count(0),
		file(file_),
		eof(false)
	{
		next_byte();
	}

	PlatformReadStream(const PlatformReadStream&) = delete;
	PlatformReadStream& operator=(const PlatformReadStream&) = delete;
	PlatformReadStream(PlatformReadStream&&)noexcept = delete;
	PlatformReadStream& operator=(PlatformReadStream&&)noexcept = delete;

	Ch Peek() const {
		return *buffer_start;
	}

	Ch Take() {
		const char c = *buffer_start;
		next_byte();
		return c;
	}

	size_t Tell() {
		const auto result = count + (
			reinterpret_cast<ptrdiff_t>(buffer_start) -
			reinterpret_cast<ptrdiff_t>(buffer));
		return result;
	}

	void Put(Ch) { RAPIDJSON_ASSERT(false); }
	void Flush() { RAPIDJSON_ASSERT(false); }
	Ch* PutBegin() { RAPIDJSON_ASSERT(false); return 0; }
	size_t PutEnd(Ch*) { RAPIDJSON_ASSERT(false); return 0; }

private:

	void next_byte() {
		if(buffer_start < buffer_end){
			buffer_start++;
		}
		else if(!eof) {
			count += bytes_read;
			bytes_read = file.read(buffer, buffer_size);

			buffer_start = &buffer[0];
			buffer_end = &buffer[bytes_read-1];

			if(bytes_read < buffer_size){
				buffer[bytes_read] = '\0';
				buffer_end++;
				eof = true;
			}
		}
	}

	char *buffer;
	char *buffer_start;
	char *buffer_end;
	size_t buffer_size;
	size_t bytes_read;
	size_t count;
	platform::file &file;
	bool eof;
};

}
