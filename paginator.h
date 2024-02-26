#pragma once

#include "document.h" 

#include <iostream>
#include <vector>
#include <iterator>

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first_(begin)
        , last_(end)
        , size_(distance(first_, last_)) {
    }

    Iterator begin() const {
        return first_;
    }

    Iterator end() const {
        return last_;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first_, last_;
    size_t size_;
};

template <typename Iterator>
std::ostream& operator<<(std::ostream& out, const IteratorRange<Iterator>& range) {
    for (Iterator it = range.begin(); it != range.end(); ++it) {
        out << *it;
    }
    return out;
}


template <typename it>
class Paginator  {
public:
    Paginator(it begin, it end,  size_t page_size) {
        for (size_t left = distance(begin, end); left > 0;) {
             size_t cp_size = std::min(page_size, left);
            const it cp_end = next(begin, cp_size);
            pages_.push_back({begin, cp_end});

            left -= cp_size;
            begin = cp_end;
        }
    }

    auto begin() const {
        return pages_.begin();
    }

    auto end() const {
        return pages_.end();
    }

    size_t size() const {
        return pages_.size();
    }

private:
    std::vector<IteratorRange<it>> pages_;
};

template <typename Cont>
auto Paginate(const Cont& c, size_t ps) {
    return Paginator(begin(c), end(c), ps);
}


using namespace std;
ostream& operator<<(ostream& os, const Document& d) {
    os<<"{ document_id = " << d.id << ", relevance = " << d.relevance <<", rating = "<<d.rating<<" }";
    return os;
}
