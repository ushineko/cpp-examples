#include "tokenizer.h"
#include <iostream>

namespace libnj { namespace util {

    /**
     * ctor; init iterators to default.
     */
    tokenizer::tokenizer() {
        iter_ = boost::algorithm::split_iterator<std::string::const_iterator>{};
        end_iter_ = boost::algorithm::split_iterator<std::string::const_iterator>{};
    }
    tokenizer::~tokenizer() { }

    /**
     * given data and splitter string, initialize the internal iterator
     * @param data
     * @param splitter
     */
    void tokenizer::split(const std::string &data, const std::string &splitter) {
        using si = boost::algorithm::split_iterator<std::string::const_iterator>;
        iter_ = boost::algorithm::make_split_iterator(data,
            boost::algorithm::first_finder(splitter,
                boost::algorithm::is_iequal()));
    }

    /**
     * get the next sequence at iterator and advance it
     * @param token token (not including splitter)
     * @return true if token was available, false if not (at end)
     */
    bool tokenizer::next(std::string &token) {
        if (iter_ == end_iter_) return false;
        token.assign(iter_->begin(), iter_->end());
        ++iter_;
        return true;
    }
}}
