/**
 * logger header
 */

#ifndef CPP_LIBNJ_UTIL_LOGGER_H
#define CPP_LIBNJ_UTIL_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace libnj { namespace util {
    class logger {
    public:
        explicit logger(std::string name="log") noexcept;
        ~logger() = default;
        std::shared_ptr<spdlog::logger> &instance();
    private:
        std::shared_ptr<spdlog::logger> instance_;
    };
}}

#endif //CPP_LIBNJ_UTIL_LOGGER_H
