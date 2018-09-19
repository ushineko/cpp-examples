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
#include "zmq_payload.pb.h"

auto lg = libnj::util::logger("zmq_worker").instance();

int main() {
    lg->info("starting worker");
    zmq::context_t context(1);

    // receiving work request from ventilator
    zmq::socket_t job_socket(context, ZMQ_PULL);
    job_socket.connect(zmq_config::worker_connect_ventilator);
    lg->info("ventilator @ {}",zmq_config::worker_connect_ventilator);

    // sending work result to sink
    zmq::socket_t result_socket(context, ZMQ_PUSH);
    result_socket.connect(zmq_config::worker_connect_sink);
    lg->info("sink @ {}",zmq_config::worker_connect_sink);

    // init curl
    libnj::net::curlinit i;
    libnj::net::curl curl;

    lg->info("entering processing loop");

    // process tasks in a loop.
    uint32_t processed_count=0;
    std::ostringstream extra;
    // our current pid
    pid_t pid = getpid();
    while(1) {
        zmq::message_t message;
        job_socket.recv(&message);
        lg->info("got job data sz={}",message.size());

        zmq_payload::Task task;
        task.ParseFromString(std::string(static_cast<char*>(message.data()),message.size()));

        zmq_payload::Result result;
        result.set_payload(task.payload());
        result.set_job_id(task.job_id());

        extra << pid << ":" << processed_count;

        switch(task.type()){
            case zmq_payload::LOOKUP: {
                lg->info("looking up {}", task.payload());
                libnj::net::ep::endpoints ep;
                libnj::net::ep::lookup(task.payload(), ep);
                for (auto e : ep) {
                    std::string ipv4 = e.address().to_v4().to_string();
                    result.add_ipv4_addresses(ipv4);
                }
                extra << ":" << result.ipv4_addresses_size();
                break;
            }
            case zmq_payload::DOWNLOAD: {
                lg->info("downloading {}", task.payload());
                curl.download(task.payload());
                const std::string &downloaded = curl.get_data();
                extra << pid << ":" << processed_count << ":" << downloaded.size();
                break;
            }
            default:
                break;
        }

        result.set_status(extra.str());

        std::string result_str;
        result.SerializeToString(&result_str);

        // send result to sink
        libnj::net::zmq_helpers::send_message(result_socket,result_str);
        lg->info("sent result to sink ({} {} {})",pid,processed_count,extra.str());
        processed_count++;
        extra.str("");
    }
}
