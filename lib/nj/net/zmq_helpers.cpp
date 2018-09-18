#include "zmq_helpers.h"

namespace libnj { namespace net {

        /**
         * send message on socket
         * @param socket valid zmq socket
         * @param msg message
         */
        void zmq_helpers::send_message(zmq::socket_t &socket, const std::string &message) {
            zmq::message_t msg(message.size());
            ::memcpy(msg.data(), message.c_str(), message.size());
            socket.send(msg);
        }

    }
}
