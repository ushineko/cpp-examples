cmake_minimum_required(VERSION 3.12)
project(nj_fs)

set(BOOST_LIBRARIES boost_filesystem boost_system)
add_library(nj_fs SHARED fs.cpp)
target_link_libraries (nj_fs ${BOOST_LIBRARIES})

