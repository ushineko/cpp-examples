#ifndef CPP_ZMQ_CONFIG_H
#define CPP_ZMQ_CONFIG_H

// poor man's config file.
namespace zmq_config {

    // address to bind for worker comms
    std::string to_worker_bind_addr("tcp://*:30001");

    // address to connect for sink coordination
    std::string to_sink_conn_addr("tcp://localhost:30002");
};

#endif //CPP_ZMQ_CONFIG_H
