#define BOOST_TEST_MODULE network_test

#include <iostream>
#include <fstream>
#include <boost/test/included/unit_test.hpp>

#include "lib/example/logger.h"
#include "lib/example/util.h"
#include "lib/example/network.h"

auto lg = example::logger().instance();

BOOST_AUTO_TEST_CASE(network_test_name_lookup) {
    lg->info("Starting tests");
    std::string host("www.attackiq.com");
    example::network::ep_list endpoints;
    example::network::dns_lookup(host,endpoints);
    lg->info("Host {} has {} endpoint(s)",host,endpoints.size());

    // sort list
    std::sort(endpoints.begin(),endpoints.end());

    for (auto e : endpoints) {
        lg->info("IP: {}",e.address().to_string());
    }
    BOOST_TEST(endpoints.size() >= 2);
    BOOST_TEST(endpoints[0].address().to_string() == "34.208.114.108");
    BOOST_TEST(endpoints[1].address().to_string() == "54.202.218.164");
}
