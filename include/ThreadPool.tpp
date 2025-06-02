#pragma once
template<class F, class... Args>
void ThreadPool::enqueue(F&& f, Args&&... args) {
    {
        std::lock_guard<std::mutex> lg(qMtx);
        tasks.emplace([t = std::bind(std::forward<F>(f), std::forward<Args>(args)...)] {
            t();
        });
    }
    cv.notify_one();
}