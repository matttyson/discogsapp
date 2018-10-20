# discogsapp

This is currently an experimental project to play with C++17.  Don't expect too much from it yet.  It's nowhere near complete or usable.

It's envisioned to be a cross platform C++ library for talking to the [discogs](http://www.discogs.com/) REST [API](https://www.discogs.com/developers/), along with a command line driver and maybe down the track a GUI app.

## libdiscogs

This is a C++ static library to talk to the [REST API](https://www.discogs.com/developers/)

## discogscli

This is a command line driver that makes use of the libdiscogs library

## Building

CMake is used to to the build.  Instructions for Windows and Linux are below.

### Windows:

* Visual Studio 2017
* [cpprestsdk](https://github.com/Microsoft/cpprestsdk)
* [rapidjson](https://github.com/Tencent/rapidjson)
* [zlib](https://zlib.net)
* patched [cxxops](https://github.com/matttyson/cxxopts/tree/wstring) library, wstring branch.

cpprestsdk can be built on Windows with CMake. We don't need websockets for this so we can skip having to build boost and openssl by excluding websockets from the build.  The following cmake args can be used to build cpprestsdk:

* `CPPRESTSDK_EXCLUDE_WEBSOCKETS=ON`
* `BUILD_SHARED_LIBS=OFF` (for static build)
* `ZLIB_LIBRARY=C:\path\to\zlib.lib`
* `ZLIB_INCLUDE_DIR=C:\path\to\include`

The app itself will need the following args passed to cmake when building on windows

* `CPPRESTSDK_LIBRARY=C:\path\to\cpprest_2_10d.lib`
* `CPPRESTSDK_INCLUDE_DIR=C:\path\to\include\cpprest`
* `ZLIB_LIBRARY=C:\path\to\zlib.lib`
* `CXXOPTS_INCLUDE_DIR=C:\path\to\cxxopts\include`
* `RAPIDJSON_INCLUDE_DIR=C:\path\to\rapidjson\include`

### Linux

rapidjson and the cpprestsdk are available in most distros package managers.  Installing the devel packages is normally sufficcent.  cxxopts is not packaged in a distro and must be downloaded manually.

* GCC 7 or later.
* [rapidjson](https://github.com/Tencent/rapidjson)
* [cpprestsdk](https://github.com/Microsoft/cpprestsdk)
* [cxxopts](https://github.com/jarro2783/cxxopts)

When building on linux you must provide the location of the cxxopts headers

* `CXXOPTS_INCLUDE_DIR=/path/to/cxxopts/include`

## TODO

Just about everything.
