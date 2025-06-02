#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t n = std::thread::hardware_concurrency());
    ~ThreadPool();

    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args);

    void stop() { stopFlag.store(true); cv.notify_all(); }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex qMtx;
    std::condition_variable cv;
    std::atomic<bool> stopFlag{false};
    void workerLoop();
};

#include "ThreadPool.tpp"