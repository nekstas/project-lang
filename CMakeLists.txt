cmake_minimum_required(VERSION 3.29)
project(project-lang)

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(
    DEBUG_TOKENS
    DEBUG_AST
    DEBUG_HLIR
    DEBUG_LLIR
)

add_subdirectory(src)
add_subdirectory(tests)
