/**
 * filesystem example library header
 */

#ifndef CPP_EXAMPLES_FS_H
#define CPP_EXAMPLES_FS_H

#include <vector>
#include <boost/filesystem.hpp>

namespace examplefs {

    /**
    * wrapper class for reading directory contents
    */
    class directory_reader {
    public:
        explicit directory_reader(boost::filesystem::path &);

        ~directory_reader();

        const std::vector<boost::filesystem::path> &operator()();

    private:
        boost::filesystem::path path_;
        std::vector<boost::filesystem::path> paths_;
    };
}

#endif //CPP_EXAMPLES_FS_H
