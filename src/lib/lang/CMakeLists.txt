add_library(lib_lang STATIC
    source/token.hpp
    source/span.cpp
    source/line_column.cpp
    source/line_column_length.cpp
    source/file.cpp
    source/program.cpp
    source/path.cpp
    frontend/file_reader/file_reader.hpp
    diag/diag.cpp
    engines/diagnostics.cpp
    frontend/file_reader/file_reader.hpp
    frontend/lexer/lexer.hpp
    frontend/lexer/impl/regex_lexer.hpp
    frontend/tokens_filter/tokens_filter.hpp
    frontend/tokens_filter/impl/simple_tokens_filter.hpp
    engines/sources.cpp
    source/source.cpp
    stats/src/stats.cpp
    stats/src/analyzer.cpp
    render/span.cpp
    render/line_span.cpp
    render/line_highlight.cpp
    source/index.cpp
    errors/errors.cpp
    frontend/tokens.hpp
)

target_link_libraries(lib_lang PRIVATE lib_errors lib_utils lib_flow)
