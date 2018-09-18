#include "logger.h"

namespace libnj { namespace util {

    logger::logger(std::string name) noexcept {
        instance_ = spdlog::stdout_color_mt(name);
        instance_->set_pattern("[%H:%M:%S:%f %z] [%n::%l] [thread %t] %v");
    }

    std::shared_ptr<spdlog::logger> &logger::instance() {
        return instance_;
    }
}}
