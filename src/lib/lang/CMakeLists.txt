add_library(lib_lang STATIC
    source/token.hpp
    source/span.cpp
    source/line_column.cpp
    source/file.cpp
    source/path.cpp
    source/path.h
    frontend/read_file/read_file.hpp
    context/base_context.h
    diag/diag.cpp
    diag/diag.h
    diag/diag_engine.cpp
    diag/diag_engine.h
    diag/list/list.h
    macros.h
    context/consts.h
)

target_link_libraries(lib_lang PRIVATE lib_errors lib_utils lib_flow)