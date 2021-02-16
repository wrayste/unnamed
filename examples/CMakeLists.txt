file(GLOB SRCS *.cpp)
add_executable(example_tests ${SRCS})
target_link_libraries(example_tests ${CONAN_LIBS_CATCH2} rapidcheck-ext)
add_test(NAME ExampleTests COMMAND example_tests)
