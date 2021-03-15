file(GLOB SRCS *.cpp)
add_executable(leet_code_tests ${SRCS})
target_link_libraries(leet_code_tests rapidcheck-ext ${CONAN_LIBS_CATCH2})
add_test(NAME LeetCodeTests COMMAND leet_code_tests)
