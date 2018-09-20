/**
 * the ventilator is the task generator. it accepts connections from workers, and
 * connects to the sink to synchronize the start of a batch. this process only lives
 * for as long as it needs to and exits when all tasks have been sent.
 */
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

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

auto lg = libnj::util::logger("zmq_ventilator").instance();

int main (int argc, char **argv) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "help!")
        ("input,i", boost::program_options::value<std::string>(), "input file");

    boost::program_options::variables_map opts;
    boost::program_options::store(
        boost::program_options::parse_command_line(argc,argv,desc),opts);
    boost::program_options::notify(opts);

    if  (opts.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    if (!opts.count("input")){
        std::cout << "Error: input file is required" << std::endl;
        return 1;
    }

    auto input_file = opts["input"].as<std::string>();

    if (!boost::filesystem::exists(input_file)) {
        std::cout << "Error: input file " << input_file << " does not exist" << std::endl;
        return 1;
    }

    // initialize line by line file reader
    boost::filesystem::path p(input_file);
    libnj::fs::line_reader reader(p);

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
    zmq_payload::Result marker;
    marker.set_status("0");
    std::string marker_data;
    marker.SerializeToString(&marker_data);
    libnj::net::zmq_helpers::send_message(to_sink,marker_data);
    lg->info("notifying sink and starting batch.");

    std::string line;
    uint32_t line_count = 0;
    uint32_t job_id=0;
    while(reader.readline(line)) {
        // first field is the alexa rank, second is the hostname (site)
        libnj::util::tokenizer t;
        t.split(line,",");
        std::string alexa_rank ; t.next(alexa_rank);
        std::string hostname ; t.next(hostname);
        if (alexa_rank.empty()) continue; // skip empty lines
        zmq_payload::Task task;
        lg->info("alexa_rank={} hostname={}",alexa_rank,hostname);
        task.set_payload(hostname);
        task.set_alexa_rank(boost::lexical_cast<int>(alexa_rank.data()));
        task.set_job_id(job_id++);
        std::string data;
        task.SerializeToString(&data);
        libnj::net::zmq_helpers::send_message(to_worker,data);
        if (line_count % 10 == 0) { lg->info("[{}]",line_count); }
        line_count++;
    }

    lg->info("sent all workloads. done.");
    // settle
    sleep(1);
    return 0;
}
