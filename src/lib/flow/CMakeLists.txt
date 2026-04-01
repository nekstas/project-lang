add_library(lib_flow INTERFACE)

target_sources(lib_flow INTERFACE
    stage.hpp
    typed_stage.hpp
    dynamic_pipeline.hpp
    static_pipeline.hpp
    utils.hpp
    map_pipeline.hpp
    stop_pipeline.hpp
    titled_pipeline.h
)

target_link_libraries(lib_flow INTERFACE lib_errors lib_utils)
