#include "file.hpp"
#include <memory>

#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>
#include <rapidjson/writer.h>
#include <rapidjson/stream.h>
#include <rapidjson/prettywriter.h>

#include "platform_rjs.hpp"

#include <cassert>

// RapidJSON file reader and writer classes

/*
	Instead of using rapidjson::GenericReader and rapidjson::Writer use the typedefs
	at the end of the file.

	platform::PrettyFileWriter;
	platform::FileWriter;
	platform::Reader;

	These are typedefs around the rapidjson types that will do the correct UTF 8/16
	conversions for the native platform string size.
*/

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
	{
		assert(file_.is_open());
		assert(buffer_size > 4);
	}

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

	// Not implemented
	Ch Peek() const { assert(false); return 0; }
	Ch Take() { assert(false); return 0; }
	size_t Tell() const { assert(false); return 0; }
	Ch* PutBegin() { assert(false); return 0; }
	size_t PutEnd(Ch*) { assert(false); return 0; }

private:
	char *buffer;
	size_t buffer_size;
	size_t count;
	platform::file &file;
};

inline void PutUnsafe(PlatformWriteStream &stream, char c) {
	stream.Put(c);
}

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
		assert(file_.is_open());
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

	void Put(Ch) { assert(false); }
	void Flush() { assert(false); }
	Ch* PutBegin() { assert(false); return 0; }
	size_t PutEnd(Ch*) { assert(false); return 0; }

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

typedef rapidjson::PrettyWriter<PlatformWriteStream, rjs_UTF_t, rapidjson::UTF8<> > PrettyFileWriter;
typedef rapidjson::Writer<PlatformWriteStream, rjs_UTF_t, rapidjson::UTF8<> > FileWriter;
typedef rapidjson::GenericReader<rapidjson::UTF8<>, rjs_UTF_t> Reader;

}
