file(GLOB SRCS *.cpp)
add_executable(project_euler_tests ${SRCS})
target_link_libraries(project_euler_tests ${CONAN_LIBS_CATCH2})
add_test(NAME ProjectEulerTests COMMAND project_euler_tests)
