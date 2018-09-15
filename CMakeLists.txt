cmake_minimum_required(VERSION 3.12)
project(cpp-examples)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_STANDARD 14)

set(BOOST_LIBRARIES boost_filesystem boost_system)

include_directories(lib/example)
add_library(examplefs SHARED lib/example/fs.cpp)

add_executable(printer printer.cpp)
add_executable(filesystem filesystem.cpp lib/example/fs.h)
add_dependencies(filesystem examplefs)

target_link_libraries (examplefs ${BOOST_LIBRARIES})
target_link_libraries (filesystem examplefs)
