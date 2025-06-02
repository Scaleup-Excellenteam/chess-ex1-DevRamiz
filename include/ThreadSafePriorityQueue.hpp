#pragma once
#include <queue>
#include <mutex>

template<class T, class Compare = std::less<T>>
class ThreadSafePriorityQueue {
public:
    void push(const T& v) {
        std::lock_guard<std::mutex> lg(mtx);
        pq.push(v);
    }
    bool poll(T& out) {
        std::lock_guard<std::mutex> lg(mtx);
        if (pq.empty()) return false;
        out = pq.top(); pq.pop();
        return true;
    }
private:
    std::priority_queue<T,std::vector<T>,Compare> pq;
    std::mutex mtx;
};