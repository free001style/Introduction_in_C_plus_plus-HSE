#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class Zipped {
public:
    Zipped(Iterator, Iterator, Iterator, Iterator);
    class CIterator {
    private:
        Iterator cur1_;
        Iterator cur2_;

    public:
        CIterator(Iterator, Iterator);
        bool operator!=(const CIterator&);
        CIterator& operator++();
        ZippedPair operator*();
    };
    CIterator begin();  // NOLINT
    CIterator end();    // NOLINT

private:
    Iterator a_begin_, a_end_, b_begin_, b_end_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
