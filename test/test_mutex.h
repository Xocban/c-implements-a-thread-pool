//
// Created by River X on 2022/8/30.
// TODO: 避免线程中因为数据共享产生的错误
//

#ifndef TEST_MUTEX_H
#define TEST_MUTEX_H

#include <list>
#include <mutex>
#include <algorithm>
#include <thread>

/*
 * TODO: 实例化std::mutex 创建互斥量，使用成员函数lock()进行上锁，unlock()解锁，此方法不推荐
 * warning: 如果采用成员函数的方法对函数上锁，则每次得在函数出口调用该成员函数unlock()，比较麻烦。
 * keypoint: 推荐采用模版类std::lack_guard<>，其会在构造函数调用对时候上锁，对象销毁时调用析构函数解锁。
 * TODO: 下面的函数进行展示
 */

extern int big_num ;

void
add_to_list(int new_value);

bool
list_contains(int value_to_find);


void
to_zero();

void
start_thread();

class some_data {
    int a;
    std::string b;
public:
    void do_something();
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func) {
        std::lock_guard<std::mutex> guard(m);
        func(data);
    }
};

extern some_data* unprotected;

void
malicious_function(some_data &protected_data);

extern data_wrapper x;

void
foo();

#endif //TEST_MUTEX_H
