add_library(codec)
target_sources(codec
        PRIVATE
        SensorInfo.cpp)
target_include_directories(codec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(codec sensor_protobuf)