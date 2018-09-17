#include "net.h"

namespace libnj { namespace net {
    /**
     * resolve endpoints given the hostname
     * @param host name of host as string, e.g. "www.google.com"
     * @param epvec vector of boost endpoints, suitable for further processing by caller
     */
    void ep::lookup(const std::string &host, endpoints &epvec) {
        boost::asio::io_service io;
        boost::asio::ip::tcp::resolver res(io);
        boost::asio::ip::tcp::resolver::query q(host,"");
        boost::asio::ip::tcp::resolver::iterator it = res.resolve(q);
        for (; it != boost::asio::ip::tcp::resolver::iterator(); ++it) {
            epvec.push_back(*it);
        }
    }
}}
