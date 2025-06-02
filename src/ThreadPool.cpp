#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t n) {
    for (size_t i = 0; i < n; ++i)
        workers.emplace_back(&ThreadPool::workerLoop, this);
}
ThreadPool::~ThreadPool() {
    stopFlag.store(true);
    cv.notify_all();
    for (auto& t : workers) if (t.joinable()) t.join();
}
void ThreadPool::workerLoop() {
    for (;;) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> ul(qMtx);
            cv.wait(ul, [&]{ return stopFlag || !tasks.empty(); });
            if (stopFlag && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}