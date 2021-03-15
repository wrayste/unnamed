file(GLOB SRCS *.cpp)
add_executable(geeks_for_geeks_tests ${SRCS})
target_link_libraries(geeks_for_geeks_tests rapidcheck-ext ${CONAN_LIBS_CATCH2})
add_test(NAME GeeksForGeeksTests COMMAND geeks_for_geeks_tests)
