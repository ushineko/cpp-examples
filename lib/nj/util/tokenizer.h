#ifndef CPP_LIBNJ_UTIL_TOKENIZER_H
#define CPP_LIBNJ_UTIL_TOKENIZER_H

#include <boost/algorithm/string.hpp>

namespace libnj { namespace util {

    class tokenizer {
    public:
        tokenizer();
        ~tokenizer();
        void split(const std::string &splitter, const std::string &data);
        bool next(std::string &token);
    private:
        boost::algorithm::split_iterator<std::string::const_iterator> iter_;
        boost::algorithm::split_iterator<std::string::const_iterator> end_iter_;
    };
}}

#endif //CPP_LIBNJ_UTIL_TOKENIZER_H
