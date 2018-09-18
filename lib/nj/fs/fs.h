/**
 * filesystem example library header
 */

#ifndef CPP_LIBNJ_FS_H
#define CPP_LIBNJ_FS_H

#include <vector>
#include <boost/filesystem.hpp>

namespace libnj { namespace fs {

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

    std::ifstream::pos_type readfile(const std::string &, std::string &);

    /**
     * wrapper class for reading a file a line-at-a-time until EOF
     */
    class line_reader {
    public:
        explicit line_reader(boost::filesystem::path &);
        ~line_reader();
        bool readline(std::string &);
    private:
        std::ifstream stream_;
    };
}}

#endif //CPP_LIBNJ_FS_H
