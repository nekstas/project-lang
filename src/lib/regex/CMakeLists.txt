add_library(lib_regex STATIC
    ast/nodes_base_node.cpp
    ast/repeat_node.cpp
    utils/indentable.cpp
    parser/parser.cpp
    visitors/ast_printer.cpp
    visitors/formatter.cpp
    utils/utils.cpp
    utils/utils.h
    visitors/nfa_builder.cpp
    nfa/state.cpp
    nfa/data.cpp
    nfa/nfa.cpp
    nfa/state_wrapper.cpp
    nfa/data_wrapper.cpp
)

target_link_libraries(lib_regex PRIVATE lib_utils)
