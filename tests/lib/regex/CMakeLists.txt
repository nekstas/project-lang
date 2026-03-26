target_sources(test_lib PRIVATE
    test_ast_nodes.cpp
    test_parser_errors.cpp
    test_ast_printer.cpp
    test_formatter.cpp
    test_nfa.cpp
)
target_link_libraries(test_lib PRIVATE
    lib_utils lib_errors lib_regex
)
