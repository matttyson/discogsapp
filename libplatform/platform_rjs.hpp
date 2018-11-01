#pragma once

#ifdef PLATFORM_WCHAR
typedef rapidjson::UTF16<> rjs_UTF_t;
#else
typedef rapidjson::UTF8<> rjs_UTF_t;
#endif
