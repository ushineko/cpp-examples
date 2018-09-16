#define BOOST_TEST_MODULE filesystem_test

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "lib/example/fs.h"
#include "lib/example/logger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

auto lg = example::logger().instance();

BOOST_AUTO_TEST_CASE(filesystem_test) {
    lg->info("Starting tests");
    boost::filesystem::path path(".");
    examplefs::directory_reader reader(path);
    const std::vector<boost::filesystem::path> &paths = reader();
    for (auto &p : paths) {
        lg->info("{0}",p.relative_path().string());
    }
    BOOST_TEST(paths.size() == 7);
    BOOST_TEST(paths[0] == "./untitled.cbp");
}

