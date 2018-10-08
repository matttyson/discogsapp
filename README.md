# discogsapp

This is currently an experimental project to play with C++17.  Don't expect too much from it yet.  It's nowhere near complete or usable.

It's envisioned to be a cross platform C++ library for talking to the [discogs](http://www.discogs.com/) REST [API](https://www.discogs.com/developers/), along with a command line driver and maybe down the track a GUI app.

## libdiscogs

This is a C++ static library to talk to the [REST API](https://www.discogs.com/developers/)

## discogscli

This is a command line driver that makes use of the libdiscogs library

## Requirements

* GCC 7 or Visual Studio 2017.
* [Rapidjson](https://github.com/Tencent/rapidjson)
* [cpprestsdk](https://github.com/Microsoft/cpprestsdk)
* patched [cxxops](https://github.com/matttyson/cxxopts/tree/wstring) library, wstring branch.

## TODO

Just about everything.

