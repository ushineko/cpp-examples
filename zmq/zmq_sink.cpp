/**
 * the sink collects and records results from the workers.
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

auto lg = libnj::util::logger("zmq_sink").instance();

int main () {
    lg->info("starting");
    zmq::context_t context(1);

    zmq::socket_t from_worker_or_ventilator(context, ZMQ_PULL);
    from_worker_or_ventilator.bind(zmq_config::sink_listen_worker_or_ventilator);

    while(1) {
        // get message. may come from either a finished worker or the ventilator.
        // ventilator messages are to indicate start of a batch
        zmq::message_t message;
        from_worker_or_ventilator.recv(&message);
        lg->info("got message: {}",message.str());
    }
}
