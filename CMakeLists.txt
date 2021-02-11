PROJECT(radionica)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-I/Library/Developer/CommandLineTools/SDKs/MacOSX11.0.sdk/usr/include -g -Wall -Werror -std=c++2a")

include(build/conanbuildinfo.cmake)
conan_basic_setup()

ENABLE_TESTING()

ADD_SUBDIRECTORY(examples)
