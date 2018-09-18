cmake_minimum_required(VERSION 3.12)
project(cpp-examples)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS lib/protobuf/example.proto)

add_subdirectory(lib/nj/fs)
add_subdirectory(lib/nj/net)
add_subdirectory(lib/nj/util)

add_executable(test_printer tests/test_printer.cpp)

add_executable(test_fs tests/test_fs.cpp)
target_link_libraries (test_fs nj_fs nj_util)

add_executable(test_protobuf tests/test_protobuf.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(test_protobuf nj_util ${BOOST_LIBRARIES} ${Protobuf_LIBRARIES})

add_executable(test_util tests/test_util.cpp)
target_link_libraries(test_util nj_util nj_fs)

add_executable(test_net tests/test_net.cpp)
target_link_libraries(test_net nj_util nj_net)

add_executable(test_curl tests/test_curl.cpp)
target_link_libraries(test_curl nj_util nj_net)

# needed for tests that require input/output
add_custom_target(data)
add_custom_command(
        TARGET data POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/data/*.txt ${CMAKE_CURRENT_BINARY_DIR})

# cmake has no included configuration for zmq.
add_executable(zmq_test_server zmq/test_server.cpp)
target_link_libraries(zmq_test_server nj_util nj_net)

add_executable(zmq_test_client zmq/test_client.cpp)
target_link_libraries(zmq_test_client nj_util nj_net)
