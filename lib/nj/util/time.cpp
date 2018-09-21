#include "time.h"

namespace libnj { namespace util {
        /**
         * return time right now in seconds.
         * @return time in seconds as std::time_t
         */
        std::time_t time::now() {
            return (boost::posix_time::to_time_t(
                    boost::posix_time::second_clock::universal_time()));
        }
    }
}
