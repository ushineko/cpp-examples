#define BOOST_TEST_MODULE util_test

#include <iostream>
#include <fstream>
#include <boost/test/included/unit_test.hpp>

#include "../lib/nj/fs/fs.h"
#include "../lib/nj/util/logger.h"
#include "../lib/nj/util/hexdump.h"
#include "../lib/nj/util/tokenizer.h"

auto lg = libnj::util::logger().instance();

BOOST_AUTO_TEST_CASE(util_test_hexdump) {
    lg->info("Starting tests for hexdump");

    // input
    std::string filename_in = "jabberwocky_in.txt";
    std::string data_in;
    BOOST_TEST(libnj::fs::readfile(filename_in,data_in) > 0);
    lg->info("Read {} bytes from {}",data_in.size(),filename_in);

    // expected output from hexdump
    std::string filename_out = "jabberwocky_out.txt";
    std::string data_out;
    BOOST_TEST(libnj::fs::readfile(filename_out,data_out) > 0);
    lg->info("Read {} bytes from {}",data_out.size(),filename_out);

    // test expected result
    std::string dump_out = libnj::util::hexdump(data_in,16);
    BOOST_TEST(data_out == dump_out);

    // hexdump throws if width is out of bounds
    std::string foobar("foobar");
    BOOST_CHECK_THROW(libnj::util::hexdump(foobar,128), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(util_test_tokenizer) {
    lg->info("Starting tests for tokenizer");

    libnj::util::tokenizer t;
    t.split("1/2/3/4","/");
    std::string tok;
    t.next(tok); BOOST_TEST(tok == "1");
    t.next(tok); BOOST_TEST(tok == "2");
    t.next(tok); BOOST_TEST(tok == "3");
    t.next(tok); BOOST_TEST(tok == "4");
    BOOST_TEST(t.next(tok) == false);
}
