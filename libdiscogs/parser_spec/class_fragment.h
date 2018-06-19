#ifdef RJSP_WIDE_CHAR
typedef std::wstring string_t;
typedef wchar_t char_t;
#else
typedef std::string string_t;
typedef char char_t;
#endif
