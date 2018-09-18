cmake_minimum_required(VERSION 3.12)
project(cpp-examples)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(TEST_PROTO_SRCS TEST_PROTO_HDRS lib/protobuf/example.proto)

add_subdirectory(lib/nj/fs)
add_subdirectory(lib/nj/net)
add_subdirectory(lib/nj/util)

add_executable(test_suite tests/test_suite.cpp ${TEST_PROTO_SRCS} ${TEST_PROTO_HDRS})
add_dependencies(test_suite data)
target_link_libraries(test_suite nj_util nj_fs nj_net ${Protobuf_LIBRARIES})

# needed for tests that require input/output
add_custom_target(data)
add_custom_command(
        TARGET data POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/data/*.txt ${CMAKE_CURRENT_BINARY_DIR})

add_executable(zmq_test_server zmq/test_server.cpp)
target_link_libraries(zmq_test_server nj_util nj_net)

add_executable(zmq_test_client zmq/test_client.cpp)
target_link_libraries(zmq_test_client nj_util nj_net)
