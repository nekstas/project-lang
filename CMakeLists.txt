cmake_minimum_required(VERSION 3.29)
project(project-lang)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(main
    src/main.cpp
)
target_link_libraries(main
    lib_utils lib_errors lib_regex
)
