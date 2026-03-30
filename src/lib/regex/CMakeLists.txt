add_library(lib_regex STATIC
    ast/nodes_base_node.cpp
    ast/repeat_node.cpp
    utils/indentable.cpp
    parser/parser.cpp
    visitors/ast_printer.cpp
    visitors/formatter.cpp
    visitors/nfa_builder.cpp
    fa/state.cpp
    fa/state_wrapper.hpp
    fa/fa.hpp
    fa/fa_wrapper.hpp
    nfa/state.cpp
    nfa/nfa.cpp
    nfa/state_wrapper.cpp
    nfa/nfa_wrapper.cpp
    algo/nfa/engine.cpp
    algo/nfa/matcher.cpp
    algo/matcher.cpp
    algo/dfa/builder.cpp
    algo/dfa/matcher.cpp
    dfa/dfa.cpp
    errors/errors.cpp
    ast/char_set_node.cpp
    ast/char_set_node.h
    ast/char_class_node.cpp
    compiler/compiler.cpp
)

target_link_libraries(lib_regex PRIVATE lib_errors lib_utils)
