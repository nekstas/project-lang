add_library(lib_lang STATIC
    source/token.hpp
    source/span.cpp
    source/line_column.cpp
    source/file.cpp
    source/path.cpp
    source/path.h
)

target_link_libraries(lib_lang PRIVATE lib_errors lib_utils lib_flow)