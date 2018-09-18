#define BOOST_TEST_MODULE fs_test

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "../lib/nj/fs/fs.h"
#include "../lib/nj/util/logger.h"

auto lg = libnj::util::logger().instance();

BOOST_AUTO_TEST_CASE(fs_test_directory_reader) {
    lg->info("Starting tests");
    boost::filesystem::path path(".");
    libnj::fs::directory_reader reader(path);
    const std::vector<boost::filesystem::path> &paths = reader();
    for (auto &p : paths) {
        lg->info("{0}",p.relative_path().string());
    }
    BOOST_TEST(paths.size() == 7);
    BOOST_TEST(paths[0] == "./untitled.cbp");
}

