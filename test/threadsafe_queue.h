//
// Created by River X on 2022/9/6.
//

#ifndef THREADING_THREADSAFE_QUEUE_H
#define THREADING_THREADSAFE_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>

template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex _m;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    threadsafe_queue() = default;

    threadsafe_queue(threadsafe_queue &other);

    void push(T new_value);

    void wait_and_pop(T &value);

    std::shared_ptr<T> wait_and_pop();

    bool try_pop(T& value);

    std::shared_ptr<T> tyr_pop();

    bool empty() const;

};


#endif //THREADING_THREADSAFE_QUEUE_H
