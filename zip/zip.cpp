#include "zip.h"

Zipped::CIterator::CIterator(Iterator fir, Iterator sec) {
    cur1_ = fir;
    cur2_ = sec;
}
Zipped::Zipped(Iterator a_beg, Iterator a_end, Iterator b_beg, Iterator b_end) {
    a_begin_ = a_beg;
    a_end_ = a_end;
    b_begin_ = b_beg;
    b_end_ = b_end;
}
bool Zipped::CIterator::operator!=(const CIterator& it) {
    return cur1_ != it.cur1_ && cur2_ != it.cur2_;
}
ZippedPair Zipped::CIterator::operator*() {
    return {*cur1_, *cur2_};
}
Zipped::CIterator& Zipped::CIterator::operator++() {
    cur1_++;
    cur2_++;
    return *this;
}
Zipped::CIterator Zipped::begin() {
    return Zipped::CIterator(a_begin_, b_begin_);
}
Zipped::CIterator Zipped::end() {
    size_t it_distance;
    if (std::distance(a_begin_, a_end_) <= std::distance(b_begin_, b_end_)) {
        it_distance = std::distance(a_begin_, a_end_);
    } else {
        it_distance = std::distance(b_begin_, b_end_);
    }
    for (size_t i = 0; i < it_distance; ++i) {
        ++a_begin_;
        ++b_begin_;
    }
    return Zipped::CIterator(a_begin_, b_begin_);
}
Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    return Zipped(a_begin, a_end, b_begin, b_end);
}
