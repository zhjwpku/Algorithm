#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadPool {
 public:
    ThreadPool(int thread_cnt = std::thread::hardware_concurrency()) : stop(false) {
      if (thread_cnt <= 0) {
          thread_cnt = std::thread::hardware_concurrency();
      }

      for (auto i = 0; i < thread_cnt; i++) {
        threads.emplace_back(std::thread([this]() {
                      while(true) {
                        std::unique_lock<std::mutex> lck(this->mu);
                        this->cond.wait(lck, [this] { return this->stop || !this->tasks.empty(); });

                        if (this->stop && this->tasks.empty()) {
                          return;
                        }
                        auto func = this->tasks.front();
                        this->tasks.pop();
                        lck.unlock();
                        func();
                      }
                    }));
      }
    }

    ~ThreadPool() {
      std::unique_lock<std::mutex> lck(mu);
      stop = true;
      lck.unlock();
      cond.notify_all();

      for (auto &t: threads) {
        t.join();
      }
    }

    template<typename Func, typename... Args>
    void enqueue(Func&& func, Args&&... args) {
      std::lock_guard<std::mutex> lg(mu);
      tasks.push([=]() { func(args...); });
      cond.notify_one();
    }

    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool &other) = delete;

 private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mu;
    std::condition_variable cond;
    bool stop;
};
