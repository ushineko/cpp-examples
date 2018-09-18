#define BOOST_TEST_MODULE curl_test

#include <iostream>
#include <fstream>
#include <boost/test/included/unit_test.hpp>

#include "../lib/nj/util/logger.h"
#include "../lib/nj/net/curl.h"

auto lg = libnj::util::logger().instance();

BOOST_AUTO_TEST_CASE(curl_test_easy) {
    lg->info("Starting tests for curl");

    libnj::net::curlinit i;
    libnj::net::curl curl;
    curl.set_verbose(true);

    size_t sz = curl.download("https://www.cnn.com/");
    const std::string &data = curl.get_data();

    lg->info("curl download of size {} bytes", sz);
    BOOST_TEST(sz > 0);
}
