//
// Created by River X on 2022/9/6.
//

#include "threadsafe_queue.h"

template<typename T>
threadsafe_queue<T>::threadsafe_queue(threadsafe_queue<T> &other) {
    std::lock_guard<std::mutex> lk(_m);
    this -> data_queue = other.data_queue;
}

template<typename T>
void threadsafe_queue<T>::push(T new_value) {
    std::lock_guard<std::mutex> lk(_m);
    data_queue.push(new_value);
    // TODO
    data_cond.notify_one();
}

template<typename T>
void threadsafe_queue<T>::wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lk(_m);
    data_cond.wait(lk, [this]{ return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
}

template<typename T>
std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> lk(_m);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool threadsafe_queue<T>::try_pop(T &value) {
    std::lock_guard<std::mutex> lk(_m);
    if(data_queue.empty()) {
        return false;
    }
    value = data_queue.front();
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> threadsafe_queue<T>::tyr_pop() {
    std::lock_guard<std::mutex> lk(_m);
    if(data_queue.empty()) {
        return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool threadsafe_queue<T>::empty() const {
    std::lock_guard<std::mutex> lk(_m);
    return data_queue.empty();
}