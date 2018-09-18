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

Set up instructions
---

**mac OS**

brew install zeromq curl nlohmann_json protobuf cmake spdlog boost

Make sure you have the latest Xcode tools (compiler) installed.

in lib/, do a "git clone https://github.com/zeromq/cppzmq" to
get the zeromq C++ wrapper. this does not have a brew recipe.

cmake should be the latest version (3.12)

(mkdir build && cd build && cmake ../ && make) **should** build all the binaries and unit tests.
If not, there is a library or environment set up issue most likely.

Development is done using CLion (https://www.jetbrains.com/clion/) and if you
have a recent version of this already, you may use it to build and debug as
well.

**linux / ubuntu**

none yet but packages and cmake invocation will be very similar.

**windows**

none yet but I have been careful not to use any platform-specific functionality in the
existing code, and as far as I know all of the third-party libs and tools should be 
cross-platform as well, including CLion.