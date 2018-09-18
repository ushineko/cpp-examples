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

int main () {
    lg->info("server starting");
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t socket (context, ZMQ_REP);
    std::string bind_addr("tcp://*:25555");
    socket.bind (bind_addr);

    lg->info("bound to {}",bind_addr);

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        lg->info("received request: {}", request.str());

        // send message back to client
        send_message(socket, "FROM_SERVER: A Series Of Unfortunate Events!");
    }
}
