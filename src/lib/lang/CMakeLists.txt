add_library(lib_lang STATIC
    source/token.hpp
    source/span.cpp
    source/line_column.cpp
    source/file.cpp
    source/path.cpp
    frontend/file_reader/file_reader.hpp
    diag/diag.cpp
    diag/diag.h
    engines/diagnostics.cpp
    macros.h
    frontend/lexer/impl/regex_lexer.hpp
    engines/sources.cpp
    source/source.cpp
)

target_link_libraries(lib_lang PRIVATE lib_errors lib_utils lib_flow)