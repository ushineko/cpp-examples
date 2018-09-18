#include "../lib/cppzmq/zmq.hpp"
#include "../lib/nj/util/logger.h"
#include "../lib/nj/net/zmq_helpers.h"
#include <string>
#include <iostream>

auto lg = libnj::util::logger().instance();

int main() {
    lg->info("starting client");
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::string server_addr("tcp://localhost:25555");
    socket.connect(server_addr);
    lg->info("connected to {}",server_addr);

    for (int request_nbr = 0; request_nbr != 100; request_nbr++) {
        libnj::net::zmq_helpers::send_message(socket,"FROM_CLIENT: Lemony Snicketerbottom");
        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        lg->info("Got reply #{}: {}",request_nbr,reply.str());
    }
}
