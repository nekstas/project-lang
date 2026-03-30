add_library(lang STATIC
    frontend/lexer/regex_lexer.hpp
)

target_link_libraries(lang PRIVATE lib_errors lib_utils lib_regex lib_flow lib_lang)
