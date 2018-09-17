#define BOOST_TEST_MODULE protobuf_test

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "example.pb.h"

#include "lib/nj/util/logger.h"
#include "lib/nj/util/hexdump.h"

auto lg = libnj::util::logger().instance();

BOOST_AUTO_TEST_CASE(protobuf_usage_test) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lg->info("Starting tests");

    example::Url proto_url;
    proto_url.set_url("https://www.google.com/");
    proto_url.set_parse_url(true);
    proto_url.set_lookup_dns(true);

    std::string data;
    proto_url.SerializeToString(&data);

    lg->info("created serialized data of size {}",data.size());
    lg->info("HEXDUMP:\n{}",libnj::util::hexdump(data,16));

    example::Url parsed_url;
    parsed_url.ParseFromString(data);

    BOOST_TEST((parsed_url.url()) == "https://www.google.com/");
    BOOST_TEST((parsed_url.parse_url()) == true);
    BOOST_TEST((parsed_url.lookup_dns()) == true);
}
