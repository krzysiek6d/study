find_package(Protobuf REQUIRED)
set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sensor_data.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
SET_SOURCE_FILES_PROPERTIES(${PROTO_SRC} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)
add_library(sensor_protobuf)
target_sources(sensor_protobuf
        PRIVATE
        ${PROTO_SRCS})
target_include_directories(
        sensor_protobuf
        PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(sensor_protobuf PUBLIC ${Protobuf_LIBRARIES})