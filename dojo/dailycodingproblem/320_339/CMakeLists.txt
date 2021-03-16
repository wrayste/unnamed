file(GLOB SRCS *.cpp)
add_executable(dailycodingproblem_320_339_tests ${SRCS})
target_link_libraries(dailycodingproblem_320_339_tests ${CONAN_LIBS_CATCH2})
add_test(NAME DailyCodingProblem320Tests COMMAND dailycodingproblem_320_339_tests)
