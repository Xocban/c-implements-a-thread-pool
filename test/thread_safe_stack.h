//
// Created by River X on 2022/8/30.
//

#include <deque>
#include <mutex>
#include <stack>

#ifndef THREADING_THREAD_SAFE_STACK_H
#define THREADING_THREAD_SAFE_STACK_H

/*
 * TODO: 实现一个线程安全的Stack
 * warning: this is a error function
 */


struct empty_stack: std::exception {
    const char* what () const throw() override {
        return "empty stack";
    }
};

template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    threadsafe_stack():
    data(std::stack<T>())
    {}

    threadsafe_stack(const threadsafe_stack& other);

    threadsafe_stack& operator=(const threadsafe_stack& other) = delete;

    void push(T new_data);

    std::shared_ptr<T> pop();

    void pop(T& value) ;

    bool empty() const;

};


#endif //THREADING_THREAD_SAFE_STACK_H
