/**
 * filesystem lib example implementation
 */

#include "fs.h"

namespace example {

    /**
    * create reader with fs::path
    * @param path
    */
    directory_reader::directory_reader(boost::filesystem::path &path) : path_(path) {}

    /**
    * default dtor
    */
    directory_reader::~directory_reader() {}

    /**
    * read current dir contents and return vector of paths
    * @return paths_
    */
    const std::vector<boost::filesystem::path> &directory_reader::operator()() {
        paths_.clear();
        boost::filesystem::directory_iterator dirend;
        for (boost::filesystem::directory_iterator dircur(path_); dircur != dirend; ++dircur) {
            paths_.push_back(dircur->path());
        }
        return paths_;
    }

}
