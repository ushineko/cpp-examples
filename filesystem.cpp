#define BOOST_TEST_MODULE filesystem_test
#include <boost/filesystem.hpp>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

namespace fs = boost::filesystem;

/**
 * directory reader takes a path and when called with () will return a vector of boost fs objects.
 */
class directory_reader {
public:
    /**
     * create dir reader given path
     * @param path
     */
    explicit directory_reader(fs::path &path) : path_(path) { }
    ~directory_reader() = default;

    /**
     * return the current directory
     * @return
     */
    const std::vector<fs::path> &operator ()() {
        files_.clear();
        fs::directory_iterator end;
        for (fs::directory_iterator cur(path_); cur != end; ++cur) {
            files_.push_back(cur->path());
        }
        return files_;
    }

private:
    fs::path path_;
    std::vector<fs::path> files_;
};

BOOST_AUTO_TEST_CASE(directory_reader_test) {
    fs::path path(".");
    directory_reader reader(path);
    const std::vector<fs::path> &paths = reader();
    for (auto &p : paths) {
        BOOST_TEST_MESSAGE(p.relative_path());
    }
    BOOST_TEST(paths.size() == 7);
    BOOST_TEST(paths[0] == "./untitled.cbp");
}

