#ifndef CPP_ZMQ_CONFIG_H
#define CPP_ZMQ_CONFIG_H
#include <string>
// poor man's config file.
namespace zmq_config {

    // address to bind for ventilator to worker
    std::string ventilator_listen_worker("tcp://*:30001");

    // address to connect from worker to ventilator
    std::string worker_connect_ventilator("tcp://localhost:30001");

    // address to connect from worker to sink
    std::string worker_connect_sink("tcp://localhost:30002");

    // address to bind and will accept either a v. batch message or work result
    std::string sink_listen_worker_or_ventilator("tcp://*:30002");

    // address to connect for ventilator to sink (this is the same as worker_connect_sink)
    std::string ventilator_connect_sink("tcp://localhost:30002");

    // batch size -- X jobs will be sent between acks from ventilator to sink
    uint32_t batch_size = 1000;
};

#endif //CPP_ZMQ_CONFIG_H
