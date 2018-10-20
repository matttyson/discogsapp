# discogsapp

This is currently an experimental project to play with C++17.  Don't expect too much from it yet.  It's nowhere near complete or usable.

It's envisioned to be a cross platform C++ library for talking to the [discogs](http://www.discogs.com/) REST [API](https://www.discogs.com/developers/), along with a command line driver and maybe down the track a GUI app.

## libdiscogs

This is a C++ static library to talk to the [REST API](https://www.discogs.com/developers/)

## discogscli

This is a command line driver that makes use of the libdiscogs library

## Building

This is built using CMake.  It's a bit tricky to build on Windows due to dependency issues at present.  I hope to get these resolved later.

### CMake args:

cxxopts can't be autoresolved by cmake and isn't packaged by distros, so you'll need to fetch that yourself.

`-DCXXOPTS_INCLUDE_DIR=/path/to/cxxopts/include`

### Windows:

* Visual Studio 2017
* vcpkg (rapidjson, cpprestsdk)
* patched [cxxops](https://github.com/matttyson/cxxopts/tree/wstring) library, wstring branch.

### Linux
* GCC 8.
* [Rapidjson](https://github.com/Tencent/rapidjson)
* cpprestsdk
* [cxxopts](https://github.com/jarro2783/cxxopts)

## TODO

Just about everything.

