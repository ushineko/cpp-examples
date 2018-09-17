#include <ostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include "hexdump.h"

namespace libnj { namespace util {

    /**
     * return a hex dump of every width bytes (alternating hex value with printable)
     * @param data data to dump, may be binary
     * @param width line width (must be in range)
     * @return string containing the dump. exception thrown if width out of range.
     */
    std::string hexdump(const std::string &data, int width=8) {
        // before we do anything, validate width and throw if out of bounds
        if (width < 8 || width > 32) {
            throw std::runtime_error("bad width, must be between 8 and 32");
        }
        std::ostringstream dump;
        int where = 0;
        auto hdr = [&dump, &where](){ dump << "[" << std::setw(4) << std::setfill('0') << where << "] "; };
        hdr();
        for (auto c : data) {
            if (where % width == 0 && where>0) {
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
}}
