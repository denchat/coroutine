# coroutine

C++ Coroutine in Action

[![Build status](https://ci.appveyor.com/api/projects/status/vpjssf4g6cv4a4ys/branch/dev/win32?svg=true)](https://ci.appveyor.com/project/luncliff/coroutine/branch/master)
[![Build Status](https://travis-ci.org/luncliff/coroutine.svg?branch=master)](https://travis-ci.org/luncliff/coroutine)

## How To

### Build

Please reference [`.travis.yml`](./.travis.yml) and [`appveyor.yml`](./appveyor.yml)

#### Tool Support

* Visual Studio 15 2017
  * `msvc`
* CMake + Clang 6.0+
  * `clang-cl`: for Windows with VC++ headers
  * `clang`: for Linux
  * `AppleClang`: for Mac

### Test

Example/Test codes are in [test/](./test) directory.

### Import

#### Visual Studio Project

For Visual Studio users, I recommend you to import vcxproj in [modules/win32](./modules/win32).  
But you can use CMake for Visual Studio either.

#### CMake Project

Current version doesn't export for CMake's `find_package`.  
Expect there is a higher CMake project which uses this library.

```cmake
add_subdirectory(coroutine)

target_link_libraries(your_project
PUBLIC
    coroutine
)
```

## Features

See [`interface/`](./interface)

* [channel](./interface/coroutine/channel.hpp)  
    Similar to that of [the Go language](https://golang.org/), but simplified form
* [Coroutine frame](./interface/coroutine/frame.h)    
    Helper code to support multiple compilers.
* [`class enumerable`](./interface/coroutine/enumerable.hpp)  
    Alternative type for `<experimental/generator>` where the header doesn't exists
* [`class sequence`](./interface/coroutine/sequence.hpp)  
    Asynchronous generator