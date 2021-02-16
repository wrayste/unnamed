add_library(rapidcheck-ext INTERFACE)
target_include_directories(rapidcheck-ext INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rapidcheck-ext INTERFACE ${CONAN_LIBS_RAPIDCHECK})

ADD_SUBDIRECTORY(tests)