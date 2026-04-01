add_library(lang STATIC
    frontend/lexer/regex_lexer.hpp
    frontend/parser/recursive_descent_parser.hpp
    ast/node.hpp
    ast/program.cpp
    ast/expr/lit/int_literal.cpp
    ast/expr/unary_expression.cpp
    ast/expr/function_call_expression.cpp
    ast/expr/variable_expression.cpp
    ast/visitors/ast_printer.cpp
    ast/expr/binary_expression.cpp
    ast/stmt/function_define_node.cpp
    ast/stmt/if_statement.cpp
    ast/stmt/if_else_statement.cpp
    ast/stmt/while_statement.cpp
    ast/stmt/block_statement.cpp
    ast/stmt/variable_declare_statement.cpp
    ast/stmt/assignment_statement.cpp
    ast/stmt/return_statement.cpp
    ast/stmt/function_call_statement.cpp
)

target_link_libraries(lang PRIVATE lib_errors lib_utils lib_regex lib_flow lib_lang)
