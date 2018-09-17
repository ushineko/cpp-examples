#define BOOST_TEST_MODULE util_test

#include <iostream>
#include <fstream>
#include <boost/test/included/unit_test.hpp>

#include "lib/example/logger.h"
#include "lib/example/util.h"

auto lg = example::logger().instance();

/**
 * helper func to read a file
 * @param filename name of file (full path)
 * @param data
 * @return true if file was read, false otherwise
 */
bool readfile(const std::string &filename, std::string &data) {
    std::ifstream reader(filename, std::ios::in | std::ios::binary | std::ios::ate);
    std::ifstream::pos_type sz = reader.tellg();
    if (sz < 0) return false;
    reader.seekg(0,std::ios::beg);
    std::vector<char> bytes(sz);
    reader.read(&bytes[0],sz);
    data.assign(&bytes[0],sz);
    return true;
}

BOOST_AUTO_TEST_CASE(util_test_hexdump) {
    lg->info("Starting tests for hexdump");

    // input
    std::string filename_in = "jabberwocky_in.txt";
    std::string data_in;
    BOOST_TEST(readfile(filename_in,data_in) == true);
    lg->info("Read {} bytes from {}",data_in.size(),filename_in);

    // expected output from hexdump
    std::string filename_out = "jabberwocky_out.txt";
    std::string data_out;
    BOOST_TEST(readfile(filename_out,data_out) == true);
    lg->info("Read {} bytes from {}",data_out.size(),filename_out);

    // test expected result
    std::string dump_out = example::util::hexdump(data_in,16);
    BOOST_TEST(data_out == dump_out);

    std::ofstream out("testdata");
    out << dump_out;
}
