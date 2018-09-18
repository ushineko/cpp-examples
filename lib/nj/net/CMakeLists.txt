cmake_minimum_required(VERSION 3.12)
project(nj_net)

find_package(Curl REQUIRED)
include_directories(${Curl_INCLUDE_DIRS})

set(BOOST_LIBRARIES boost_filesystem boost_system)
add_library(nj_net SHARED net.cpp curl.cpp)
target_link_libraries (nj_net ${BOOST_LIBRARIES} ${CURL_LIBRARIES})

