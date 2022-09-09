//
// Created by River X on 2022/8/30.
//

#include "thread_safe_stack.h"

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other) {
    // lock
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
}

template<typename T>
void threadsafe_stack<T>::push(T new_data) {
    // lock
    std::lock_guard<std::mutex> lock(m);
    data.push(new_data);
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop() {
    // lock
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();

    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
    data.pop();
    return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T& value) {
    // lock
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();

    value = data.top();
    data.pop();
}

template<typename T>
bool threadsafe_stack<T>::empty() const {
    // lock
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
}

