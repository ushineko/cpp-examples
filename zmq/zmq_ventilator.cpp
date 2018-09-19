/**
 * the ventilator is the task generator. it accepts connections from workers, and
 * connects to the sink to synchronize the start of a batch. this process only lives
 * for as long as it needs to and exits when all tasks have been sent.
 */
#include <iostream>
#include "../lib/nj/fs/fs.h"
#include "../lib/nj/net/curl.h"
#include "../lib/nj/net/net.h"
#include "../lib/nj/net/zmq_helpers.h"
#include "../lib/nj/util/hexdump.h"
#include "../lib/nj/util/tokenizer.h"
#include "../lib/nj/util/logger.h"

#include "../lib/cppzmq/zmq.hpp"
#include "zmq_config.h"

auto lg = libnj::util::logger("zmq_ventilator").instance();

int main (int argc, char **argv) {
    zmq::context_t context(1);
    // socket to send worker messages on
    zmq::socket_t to_worker(context, ZMQ_PUSH);
    to_worker.bind(zmq_config::ventilator_listen_worker);

    lg->info("Starting up on {}. Waiting for workers to settle...",
        zmq_config::ventilator_listen_worker);

    // workaround for slow joiner problem. wait for 5 seconds.
    sleep(5);

    // signal the start of the batch to the sink
    zmq::socket_t to_sink(context, ZMQ_PUSH);
    to_sink.connect(zmq_config::ventilator_connect_sink);

    lg->info("done. connected to sink on {}", zmq_config::ventilator_connect_sink);
    libnj::net::zmq_helpers::send_message(to_sink,"0");
    lg->info("notifying sink and starting batch.");

    // send batch of jobs...testing only
    int num_tasks=zmq_config::batch_size;
    while(num_tasks--) {
        libnj::net::zmq_helpers::send_message(to_worker,"www.google.com");
        if (num_tasks % 10 == 0) { lg->info("[{}]",num_tasks); }
    }

    lg->info("sent all workloads. done.");
    // settle
    sleep(1);
    return 0;
}
