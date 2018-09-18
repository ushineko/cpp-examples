#include "../lib/cppzmq/zmq.hpp"
#include "../lib/nj/util/logger.h"
#include <string>
#include <iostream>

auto lg = libnj::util::logger().instance();

void send_message(zmq::socket_t &socket, const std::string &message) {
    zmq::message_t msg(message.size());
    ::memcpy(msg.data(), message.c_str(), message.size());
    socket.send(msg);
}

int main() {
    lg->info("starting client");
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::string server_addr("tcp://localhost:25555");
    socket.connect(server_addr);
    lg->info("connected to {}",server_addr);

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 100; request_nbr++) {
        send_message(socket,"FROM_CLIENT: Lemony Snicketerbottom");
        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        lg->info("Got reply #{}: {}",request_nbr,reply.str());
    }
}
