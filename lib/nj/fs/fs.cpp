/**
 * filesystem lib example implementation
 */

#include "fs.h"

namespace libnj { namespace fs {

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

    /**
     * read contents from file. data is appended to.
     * @param filename file to read
     * @param data data to write as string (appended)
     * @return result from tellg(); e.g. the size of the file. -1 if read failed.
     */
    std::ifstream::pos_type readfile(const std::string &filename, std::string &data) {
        std::ifstream reader(filename, std::ios::in | std::ios::binary | std::ios::ate);
        std::ifstream::pos_type sz = reader.tellg();
        if (sz < 0) return sz;
        reader.seekg(0,std::ios::beg);
        std::vector<char> bytes(sz);
        reader.read(&bytes[0],sz);
        data.append(&bytes[0],sz);
        return sz;
    }

}}
