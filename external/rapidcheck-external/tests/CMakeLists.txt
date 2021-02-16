file(GLOB SRCS *.cpp)
add_executable(rapid_check_ext_tests ${SRCS})
target_link_libraries(rapid_check_ext_tests rapidcheck-ext)
add_test(NAME RapidCheckExtTests COMMAND rapid_check_ext_tests)