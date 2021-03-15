PROJECT(unnamed)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-I/Library/Developer/CommandLineTools/SDKs/MacOSX11.1.sdk/usr/include -g -Wall -Werror -std=c++2a")

include(build/conanbuildinfo.cmake)
conan_basic_setup()

set(ENABLE_INCLUDE_WHAT_YOU_USE TRUE)
include(cmake/StaticAnalyzers.cmake)

ENABLE_TESTING()
INCLUDE(Dart)

ADD_SUBDIRECTORY(dojo)
ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(external)
