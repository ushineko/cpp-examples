#include "network.h"

namespace example {
    /**
     * resolve endpoints given the hostname
     * @param host name of host as string, e.g. "www.google.com"
     * @param endpoints vector of boost endpoints, suitable for further processing by caller
     */
    void network::dns_lookup(const std::string &host, ep_list &endpoints) {
        boost::asio::io_service io;
        boost::asio::ip::tcp::resolver res(io);
        boost::asio::ip::tcp::resolver::query q(host,"");
        boost::asio::ip::tcp::resolver::iterator it = res.resolve(q);
        for (; it != boost::asio::ip::tcp::resolver::iterator(); ++it) {
            endpoints.push_back(*it);
        }
    }
}
