
#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>
#include <rapidjson/writer.h>

// A simple class that will just copy input to output
// This can be used with a pretty writer to create neatly formatted document.

// TODO: I'm not sure this is the best place for this class. find somewhere
// else to put it

template<typename WRITER, typename SOURCE_ENCODING = rjs_UTF_t >
class rapid_pretty_parser : public rapidjson::BaseReaderHandler<SOURCE_ENCODING, rapid_pretty_parser<WRITER, SOURCE_ENCODING>> {
public:
	typedef typename SOURCE_ENCODING::Ch Ch;

	rapid_pretty_parser(WRITER &write)
		:w(write)
	{}

	bool Null() {
		return w.Null();
	}
	bool Bool(bool b) {
		return w.Bool(b);
	}
	bool Int(int value) {
		return w.Int(value);
	}
	bool Uint(unsigned int value) {
		return w.Uint(value);
	}
	bool Int64(int64_t value) {
		return w.Int64(value);
	}
	bool Uint64(uint64_t value) {
		return w.Uint64(value);
	}
	bool Double(double value) {
		return w.Double(value);
	}
	bool String(const Ch* str, rapidjson::SizeType length, bool) {
		return w.String(str, length);
	}
	bool Key(const Ch* str, rapidjson::SizeType length, bool) {
		return w.Key(str, length);
	}
	bool StartObject() {
		return w.StartObject();
	}
	bool EndObject(rapidjson::SizeType) {
		return w.EndObject();
	}
	bool StartArray() {
		return w.StartArray();
	}
	bool EndArray(rapidjson::SizeType) {
		return w.EndArray();
	}
	bool RawNumber(const Ch *, rapidjson::SizeType, bool) {
		return false;
	}
private:
	WRITER &w;
};
