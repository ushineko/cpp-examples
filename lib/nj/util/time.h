#ifndef CPP_LIBNJ_UTIL_TIME_H
#define CPP_LIBNJ_UTIL_TIME_H
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/conversion.hpp>

namespace libnj { namespace util {
    class time {
    public:
        static std::time_t now();
    };
}}

#endif //CPP_LIBNJ_UTIL_TOKENIZER_H
