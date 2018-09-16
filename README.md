various experiments and examples for C++ (w/ several libraries)

Current list of tools/libs
--
* boost
    * boost is a C++ library supporting the latest extensions, and is the preferred way to get access to 
    many systems, network, and application programming patterns.
* spdlog
    * spdlog is a fast header-only C++ logging library, suitable for quickly generating formatted logging
    and tracing messages. 
* zeromq
    * zeromq is a lightweight, brokerless message queueing library which can be used to build fast SOA and 
    and comms architectures for applications.
* protobuf
    * protobuf is a serialization library from Google, suitable for defining and managing complex messaging
    types that can be efficiently sent over various comms channels (file/network)
* nlohmann/json
    * a header-only JSON parsing and creation library that makes JSON behave like a first-class
    datatype! slated for future inclusion into the standard, this is **the** JSON library to
    use for C++.

All libs on mac OS are either installed via brew or locally within lib/ 
(**libraries not included**)

All libs on linux are installed via apt-get or yum, otherwise they are
within lib/ (**likewise, libraries not included**)
