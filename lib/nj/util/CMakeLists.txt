cmake_minimum_required(VERSION 3.12)
project(nj_util)

set(BOOST_LIBRARIES boost_filesystem boost_system)
add_library(nj_util SHARED logger.cpp hexdump.cpp tokenizer.cpp time.cpp)
target_link_libraries (nj_util ${BOOST_LIBRARIES})

