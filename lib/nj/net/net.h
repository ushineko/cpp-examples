#ifndef CPP_LIBNJ_NET_H
#define CPP_LIBNJ_NET_H

#include <vector>
#include <boost/asio.hpp>

namespace libnj { namespace net {
    class ep {
    public:
        typedef std::vector<boost::asio::ip::tcp::endpoint> endpoints;
        static void lookup(const std::string &, endpoints&);
    };
}}

#endif //CPP_LIBNJ_NET_H
