file(GLOB SRCS *.cpp)
add_executable(dailycodingproblem_300_319_tests ${SRCS})
target_link_libraries(dailycodingproblem_300_319_tests ${CONAN_LIBS_CATCH2})
add_test(NAME DailyCodingProblem300Tests COMMAND dailycodingproblem_300_319_tests)
