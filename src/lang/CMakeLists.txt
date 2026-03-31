add_library(lang STATIC
    frontend/lexer/regex_lexer.hpp
    frontend/parser/recursive_descent_parser.hpp
    ast/node.hpp
    ast/expr/lit/int_literal.cpp
    ast/visitors/ast_printer.cpp
    ast/expr/binary_expression.cpp
)

target_link_libraries(lang PRIVATE lib_errors lib_utils lib_regex lib_flow lib_lang)
