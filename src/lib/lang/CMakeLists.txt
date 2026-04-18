add_library(lib_lang STATIC
    src/token.hpp
    src/span.cpp
    src/line_column.cpp
    src/line_column_length.cpp
    src/file.cpp
    src/path.cpp
    src/source.cpp
    src/index.cpp
    frontend/file_reader/file_reader.hpp
    diag/diag.cpp
    engines/diagnostics.cpp
    frontend/file_reader/file_reader.hpp
    frontend/lexer/lexer.hpp
    frontend/lexer/impl/regex_lexer.hpp
    frontend/tokens_filter/tokens_filter.hpp
    frontend/tokens_filter/impl/simple_tokens_filter.hpp
    engines/sources.cpp
    stats/src/stats.cpp
    stats/src/analyzer.cpp
    render/span.cpp
    render/line_span.cpp
    render/line_highlight.cpp
    errors/errors.cpp
    types.hpp
)

target_link_libraries(lib_lang PRIVATE lib_errors lib_utils lib_flow)