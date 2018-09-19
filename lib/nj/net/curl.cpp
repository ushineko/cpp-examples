#include "curl.h"

namespace libnj { namespace net {

        curl::curl() {
            curl_ = curl_easy_init();
            curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &data_);
        }

        curl::~curl() { }

        /**
         * static callback for libcurl write
         * @param buf buffer
         * @param sz size
         * @param nm num members of size (total sz to write is "sz*nm")
         * @param userp write data
         * @return bytes written
         */
        size_t curl::write_data(void *buf, size_t sz, size_t nm, void *userp) {
            size_t to_write = sz*nm;
            auto *data = static_cast<std::string *>(userp);
            data->assign(static_cast<const char *>(buf),to_write);
            return to_write;
        }

        /**
         * download specified url. data will be in data_
         * @param url URL
         * @return size downloaded, -1 if error
         */
        size_t curl::download(const std::string &url) {
            curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
            CURLcode result = curl_easy_perform(curl_);
            if (result != CURLE_OK) {
                return (size_t)-1;
            }
            return data_.size();
        }

        /**
         * return internal data buffer
         * @return data_
         */
        const std::string &curl::get_data() {
            return data_;
        }

        void curl::set_verbose(bool on) {
            curl_easy_setopt(curl_, CURLOPT_VERBOSE, on);
        }

        curlinit::curlinit() {
            curl_global_init(CURL_GLOBAL_DEFAULT);
        }
        curlinit::~curlinit() {
            curl_global_cleanup();
        }
    }
}
