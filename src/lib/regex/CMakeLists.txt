add_library(lib_regex STATIC
    ast/nodes_base_node.cpp
    ast/repeat_node.cpp
    utils/indentable.cpp
    parser/parser.cpp
    visitors/ast_printer.cpp
    visitors/formatter.cpp
    utils/utils.cpp
    utils/utils.h
)

target_link_libraries(lib_regex PRIVATE lib_utils)
