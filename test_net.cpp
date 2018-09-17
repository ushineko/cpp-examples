#define BOOST_TEST_MODULE net_test

#include <iostream>
#include <fstream>
#include <boost/test/included/unit_test.hpp>

#include "lib/nj/util/logger.h"
#include "lib/nj/net/net.h"

auto lg = libnj::util::logger().instance();

BOOST_AUTO_TEST_CASE(net_test_endpoint_lookup) {
    lg->info("Starting tests");
    std::string host("www.attackiq.com");
    libnj::net::ep::endpoints epvec;
    libnj::net::ep::lookup(host,epvec);
    lg->info("Host {} has {} endpoint(s)",host,epvec.size());

    // sort list
    std::sort(epvec.begin(),epvec.end());

    for (auto e : epvec) {
        lg->info("IP: {}",e.address().to_string());
    }
    BOOST_TEST(epvec.size() >= 2);
    BOOST_TEST(epvec[0].address().to_string() == "34.208.114.108");
    BOOST_TEST(epvec[1].address().to_string() == "54.202.218.164");
}
