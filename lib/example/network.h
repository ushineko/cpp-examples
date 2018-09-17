#ifndef CPP_EXAMPLES_NETWORK_H
#define CPP_EXAMPLES_NETWORK_H

#include <vector>
#include <boost/asio.hpp>

namespace example {
    class network {
    public:
        typedef std::vector<boost::asio::ip::tcp::endpoint> ep_list;
        static void dns_lookup(const std::string &, ep_list&);
    };
}

#endif //CPP_EXAMPLES_NETWORK_H
