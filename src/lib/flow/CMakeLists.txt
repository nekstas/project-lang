add_library(lib_flow STATIC
    stage.hpp
    typed_stage.hpp
    dynamic_pipeline.hpp
    static_pipeline.hpp
    utils.hpp
    map_pipeline.hpp
    stop_pipeline.hpp
    titled_pipeline.h
)

target_link_libraries(lib_flow PRIVATE lib_errors lib_utils)
