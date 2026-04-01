target_sources(test_lang PRIVATE
    test_lang.cpp
)

target_link_libraries(test_lang PRIVATE
    lib_utils
    lib_errors
    lib_flow
    lib_lang
    lang
)
