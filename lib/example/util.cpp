#include <ostream>
#include <iomanip>
#include <sstream>
#include "util.h"

namespace example {

    /**
     * return a hex dump of every 8 bytes (alternating hex value with printable)
     * @param data data to dump, may be binary
     * @return string containing the dump
     */
    std::string util::hexdump(const std::string &data) {
        std::ostringstream dump;
        int where = 0;
        auto hdr = [&dump, &where](){ dump << "[" << std::setw(4) << std::setfill('0') << where << "] "; };
        hdr();
        for (auto c : data) {
            if (where % 8 == 0 && where>0) {
                dump << std::endl;
                hdr();
            }
            dump << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(c)
                << std::resetiosflags(std::ios::showbase) << " ";
            ::isgraph(c) ? dump << c << " " : dump << "  ";
            where++;
        }
        return dump.str();
    }

}
