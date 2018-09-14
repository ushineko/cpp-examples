cmake_minimum_required(VERSION 3.12)
project(cpp-examples)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_LIBRARIES boost_filesystem boost_system)

add_executable(printer printer.cpp)
add_executable(filesystem filesystem.cpp)

target_link_libraries (filesystem ${BOOST_LIBRARIES})
