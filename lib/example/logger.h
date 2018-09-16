/**
 * logger header
 */

#ifndef CPP_EXAMPLES_LOGGER_H
#define CPP_EXAMPLES_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace example {
    class logger {
    public:
        explicit logger() noexcept;
        ~logger() = default;
        std::shared_ptr<spdlog::logger> &instance();
    private:
        std::shared_ptr<spdlog::logger> instance_;
    };
}

#endif //CPP_EXAMPLES_LOGGER_H
