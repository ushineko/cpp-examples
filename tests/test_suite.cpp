#define BOOST_TEST_MODULE test_suite

#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "../lib/nj/fs/fs.h"
#include "../lib/nj/net/curl.h"
#include "../lib/nj/net/net.h"
#include "../lib/nj/util/hexdump.h"
#include "../lib/nj/util/tokenizer.h"
#include "../lib/nj/util/logger.h"

#include "example.pb.h"

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

    // lookup a non existent address. this will add an "empty" endpoint to the list
    // which should resolve as a string to "0.0.0.0"
    epvec.clear();
    libnj::net::ep::lookup("kwyjibo.flpphtht",epvec);
    BOOST_TEST(epvec.size() == 1);
    BOOST_TEST(epvec[0].address().to_string() == "0.0.0.0");
}

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

BOOST_AUTO_TEST_CASE(fs_test_line_reader) {
    lg->info("Starting tests for line_reader");

    boost::filesystem::path p("jabberwocky_in.txt");
    libnj::fs::line_reader lr(p);

    std::string line;
    int num=0;
    while(lr.readline(line)) {
        lg->info("Got line: {}",line);
        num++;
    }
    lg->info("read {} lines",num);
    BOOST_TEST(num == 34);
}

BOOST_AUTO_TEST_CASE(protobuf_example_test) {
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