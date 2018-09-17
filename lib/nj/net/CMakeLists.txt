cmake_minimum_required(VERSION 3.12)
project(nj_net)

set(BOOST_LIBRARIES boost_filesystem boost_system)
add_library(nj_net SHARED net.cpp)
target_link_libraries (nj_net ${BOOST_LIBRARIES})

