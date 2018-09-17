cmake_minimum_required(VERSION 3.12)
project(cpp-examples)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS lib/protobuf/example.proto)

set(BOOST_LIBRARIES boost_filesystem boost_system)

include_directories(lib/example)
add_library(examplefs SHARED lib/example/fs.cpp)
target_link_libraries (examplefs ${BOOST_LIBRARIES})

add_library(examplelogger SHARED lib/example/logger.cpp)

add_library(exampleutil SHARED lib/example/util.cpp)

add_executable(printer printer.cpp)

add_executable(filesystem filesystem.cpp)
add_dependencies(filesystem examplefs)
target_link_libraries (filesystem examplefs examplelogger)

add_executable(protobuf protobuf.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(protobuf examplelogger exampleutil
        ${BOOST_LIBRARIES} ${Protobuf_LIBRARIES})

add_executable(util util.cpp)
add_dependencies(util data examplelogger exampleutil)
target_link_libraries(util examplelogger exampleutil ${BOOST_LIBRARIES})

# needed for tests that require input/output
add_custom_target(data)
add_custom_command(
        TARGET data POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/data/*.txt
        ${CMAKE_CURRENT_BINARY_DIR})

