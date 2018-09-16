#define BOOST_TEST_MODULE protobuf_test

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include <example.pb.h>
#include "example.pb.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

static auto console = spdlog::stdout_color_mt("protobuf");

BOOST_AUTO_TEST_CASE(protobuf_usage_test) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    console->set_pattern("[%H:%M:%S %z] [%n::%l] [thread %t] %v");
    console->info("Starting tests");

    example::Url proto_url;
    proto_url.set_url("https://www.google.com/");
    proto_url.set_parse_url(true);
    proto_url.set_lookup_dns(true);

    std::string data;
    proto_url.SerializeToString(&data);

    console->info("created serialized data of size {}",data.size());

    example::Url parsed_url;
    parsed_url.ParseFromString(data);

    BOOST_TEST(parsed_url.url() == "https://www.google.com/");
    BOOST_TEST(parsed_url.parse_url() == true);
    BOOST_TEST(parsed_url.lookup_dns() == true);
}
