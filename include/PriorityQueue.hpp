#pragma once
#include <list>
#include "ChessExceptions.hpp"

template<class T, class Comparator>
class PriorityQueue {
    std::list<T> data;
    Comparator   cmp;

public:
    std::size_t size()  const { return data.size(); }
    bool        empty() const { return data.empty(); }

    void push(const T& val)
    {
        auto it = data.begin();
        for (; it != data.end(); ++it)
            if (cmp(val, *it)) break;
        data.insert(it, val);
    }

    const T& top() const {
        if (data.empty()) throw EmptyPriorityQueueException();
        return data.front();
    }
    T poll() {
        if (data.empty()) throw EmptyPriorityQueueException();
        T best = data.front();
        data.pop_front();
        return best;
    }
};