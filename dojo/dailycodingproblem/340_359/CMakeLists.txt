file(GLOB SRCS *.cpp)
add_executable(dailycodingproblem_340_359_tests ${SRCS})
target_link_libraries(dailycodingproblem_340_359_tests ${CONAN_LIBS_CATCH2})
add_test(NAME DailyCodingProblem340Tests COMMAND dailycodingproblem_340_359_tests)
