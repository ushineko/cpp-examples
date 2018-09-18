/**
 * helpers for zmq comms
 */
#ifndef CPP_LIBNJ_NET_ZMQ_HELPERS_H
#define CPP_LIBNJ_NET_ZMQ_HELPERS_H

#include "../../cppzmq/zmq.hpp"
#include <string>

namespace libnj { namespace net {

        class zmq_helpers {
        public:
            static void send_message (zmq::socket_t &, const std::string &);
        };

    }
}


#endif //CPP_LIBNJ_NET_ZMQ_HELPERS_H
