#ifndef CPP_LIBNJ_NET_CURL_H
#define CPP_LIBNJ_NET_CURL_H

#include <curl/curl.h>
#include <string>

namespace libnj {
    namespace net {
        class curl {
        public:
            curl();
            ~curl();
            static size_t write_data(void *, size_t, size_t, void *);
            size_t download(const std::string &);
            const std::string &get_data();
            void set_verbose(bool);

        private:
            std::string data_;
            CURL *curl_;
        };

        class curlinit {
        public:
            curlinit();
            ~curlinit();
        };
    }
}


#endif //CPP_LIBNJ_NET_CURL_H
