# Catch2
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.13.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(test_lib)
target_link_libraries(test_lib PRIVATE Catch2::Catch2WithMain)
add_subdirectory(lib/regex)

add_executable(test_lang)
target_link_libraries(test_lang PRIVATE Catch2::Catch2WithMain)
add_subdirectory(lang)
