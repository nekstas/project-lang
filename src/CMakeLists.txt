add_subdirectory(lib)

add_executable(main
    main.cpp
)
target_link_libraries(main
    lib_utils lib_errors lib_regex lib_flow lib_lang
)
