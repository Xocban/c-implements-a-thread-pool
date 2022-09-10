//
// Created by River X on 2022/9/9.
//

#ifndef THREADING_THREAD_POOL_H
#define THREADING_THREAD_POOL_H

#include <iostream>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <exception>
#include <atomic>

class thread_pool {

private:

    using m_function_t = std::function<void()>;

    // using m_task_prt_t = std::shared_ptr<m_function_t>;

    using m_task_queue = std::queue<m_function_t>;

    std::condition_variable m_cond;
    /* 存放线程 */
    std::vector<std::thread> m_threads;
    /* 存放任务 */
    m_task_queue m_queue;

    std::mutex m;

    std::atomic<bool> stop_;

    // thread_guard tg_;

public:
    explicit thread_pool(std::size_t thread_count = std::thread::hardware_concurrency()):
    stop_(false)
    // tg_(m_threads)
    {
        if(thread_count <= 0) throw std::invalid_argument("thread count mast > 0\n");
        for(auto i = 0; i < thread_count; ++i) {
            /* 此处创建线程，并放入vecotr容器中 */
            m_threads.push_back(std::thread([this] {
                while (!stop_.load(std::memory_order_acquire)) {
                    m_function_t task;
                    {
                        std::unique_lock<std::mutex> lk(m);
                        m_cond.wait(lk, [this] {
                            return stop_.load(std::memory_order_acquire) || !m_queue.empty();;
                        });
                        if (stop_.load(std::memory_order_acquire))
                            return;
                        task = std::move(m_queue.front());
                        m_queue.pop();
                    }
                    // (*task)();
                    task();
                }
            }));
        }
    };

    ~thread_pool(){
        stop();
        m_cond.notify_all();
        for(auto &t: m_threads) {
            if(t.joinable())
                t.join();
        }
    }

    thread_pool(const thread_pool&) = delete;

    thread_pool& operator=(const thread_pool&) = delete;

    template<typename F, typename ...Args>
    std::future<typename std::result_of<F(Args...)>::type> add_work(F &&f, Args &&... args) {
        using return_type = typename std::result_of<F(Args...)>::type;
        using task = std::packaged_task<return_type()>;

        auto t = std::make_shared<task>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        auto ret = t -> get_future();
        {
            std::unique_lock<std::mutex> lk(m);
            if(stop_.load(std::memory_order_acquire))
                throw std::runtime_error("thread pool has stopped\n");
            m_queue.emplace([t] { (*t)(); });
            // m_queue.push(t);
        }
        m_cond.notify_one();
        return ret;
    }

    void stop() {
        stop_.store(true, std::memory_order_release);
    }

};


#endif //THREADING_THREAD_POOL_H
