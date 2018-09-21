/**
 * the sink collects and records results from the workers.
 */
#include <iostream>
#include <nlohmann/json.hpp>
#include <boost/function.hpp>

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

auto lg = libnj::util::logger("zmq_sink").instance();

/**
 * convert the pb result to a json object
 * @param result zmq_payload::Result
 * @param record json object
 */
void result_to_json(zmq_payload::Result &result, nlohmann::json &record) {
    record["job_id"]  = result.job_id();
    record["payload"] = result.payload();
    record["status"]  = result.status();
    record["time_submitted"] = result.time_submitted();
    record["time_processed"] = result.time_processed();
    record["download_size"]  = result.download_size();
    record["alexa_rank"]   = result.alexa_rank();
    record["time_elapsed"] = result.time_processed() - result.time_submitted();
    record["worker_pid"]   = result.worker_pid();

    // set the ipv4 address list
    std::vector<std::string> ipv4_addresses;
    for (int i = 0; i < result.ipv4_addresses_size(); ++i) {
        ipv4_addresses.push_back(result.ipv4_addresses(i));
    }
    record["ipv4_addresses"] = ipv4_addresses;
}

int main () {
    lg->info("starting");
    zmq::context_t context(1);

    zmq::socket_t from_worker_or_ventilator(context, ZMQ_PULL);
    from_worker_or_ventilator.bind(zmq_config::sink_listen_worker_or_ventilator);

    // open output file
    boost::filesystem::path output_file("zmq_sink_output.txt");
    std::ofstream output (output_file.relative_path().string(), std::ios::app | std::ios::ate | std::ios::binary);
    if (!output.is_open()) {
        lg->info("error: cannot open output file {}",output_file.relative_path().string());
    }

    while(1) {
        // get message. may come from either a finished worker or the ventilator.
        // ventilator messages are to indicate start of a batch
        zmq::message_t message;
        from_worker_or_ventilator.recv(&message);
        lg->info("got message of sz {}",message.size());
        zmq_payload::Result result;
        result.ParseFromString(std::string(static_cast<char *>(message.data()),message.size()));
        // check status; v. marker will always be the string "0"
        if (result.status() == "0") {
            lg->info("got ventilator marker. all is well.");
        } else {
            lg->info("got completed job:{} {} {}",
                result.job_id(),result.payload(),result.status());
            nlohmann::json record;
            result_to_json(result,record);
            output << record.dump() << std::endl;
        }
    }
}
