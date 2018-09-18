Required Libraries/Tools
--
* cmake (https://cmake.org/)
* boost (https://www.boost.org/) 
* spdlog (https://github.com/gabime/spdlog)
* zeromq (http://zeromq.org/)
* protobuf (https://developers.google.com/protocol-buffers/)
* nlohmann/json (https://github.com/nlohmann/json)
* libcurl (https://curl.haxx.se/libcurl/)

All libs on mac OS are either installed via brew or locally within lib/ 
(**libraries not included**)

All libs on linux are installed via apt-get or yum, otherwise they are
within lib/ (**likewise, libraries not included**)

libnj
--
libnj is a simple library written specifically for this project. it includes
wrappers and utilities for network, string manipulation, and logging. 

the unit test suite is written using boost test (https://www.boost.org/doc/libs/1_60_0/libs/test/doc/html/index.html)

zeromq pipeline processor
---
**(work in progress)**

the required libraries, libnj, and zeromq are used together to implement a brokerless
task pipeline, including the following parts:
* task generator / ventilator
* dynamic workers (workers can be added / removed as needed)
* task collector / sink

All service components can be run on one machine for testing or multiple machines
for scaling out. In the trivial demonstration of this pattern, we will only be
running the components on one machine.

data is marshaled between the service components using protocol buffers
and written by the collector in JSON format. 
at the moment there are only two basic tasks that can be run through the 
pipeline:
1. given a hostname/url, resolve the endpoint and return the list of IPv4 addresses associated with the endpoint.
2. given a full url, download the content and report the size of the content and 
any interesting HTTP headers to the collector.

what is **not** implemented:
* any saving of the web content (would likely be done by the workers straight to
a database/document storage)
* anything beyond simple batching by the ventilator
* although there are some stats recorded most details in the interest of time will 
be elided.
