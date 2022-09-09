//
// Created by River X on 2022/8/30.
//
//
// Created by River X on 2022/8/30.
// TODO: 避免线程中因为数据共享产生的错误
//

#define TEST_MUTEX 0
#define TEST_BIG_NUM 0
#define UNPROTECTED 0

#include <iostream>
#include "./test_mutex.h"

/*
 * TODO: 实例化std::mutex 创建互斥量，使用成员函数lock()进行上锁，unlock()解锁，此方法不推荐
 * warning: 如果采用成员函数的方法对函数上锁，则每次得在函数出口调用该成员函数unlock()，比较麻烦。
 * keypoint: 推荐采用模版类std::lack_guard<>，其会在构造函数调用对时候上锁，对象销毁时调用析构函数解锁。
 * TODO: 下面的函数进行展示
 */

#if TEST_MUTEX == 1

std::list<int> some_list;
std::mutex some_mutex;

void
add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(some_mutex); // lock
    some_list.push_back(new_value);
    // unlock
}

bool
list_contains(int value_to_find) {
    std::lock_guard<std::mutex> gurad(some_mutex); // lock
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
    // unlock
}

/*
 * TODO: 这样就保证在调用
 */

#endif // TEST_MUTEX

#if TEST_BIG_NUM == 1

int big_num = 0;

void
to_zero() {
    // big_num = 0;
    std::lock_guard<std::mutex> guard(some_mutex); // lock
    for(int i = 0; i < 10e5; ++i) {
        // ++big_num;
        ++big_num;
        // ++num;
    }
    // unlock
}

void
start_thread() {
    std::thread(to_zero).detach();
    std::thread(to_zero).detach();
}

#endif // TEST_BIG_NUM

#if UNPROTECTED == 1
/*
 * TODO: 这种情况会破坏掉对数据的保护从而使锁失效
 */
void
malicious_function(some_data &protected_data) {
    unprotected=&protected_data;
}

void
foo() {
    x.process_data(malicious_function);    // 2 传递一个恶意函数
    unprotected->do_something();    // 3 在无保护的情况下访问保护数据
}
#endif // UNPROTECTED

