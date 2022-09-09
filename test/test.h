//
// Created by River X on 2022/9/8.
//

#ifndef THREADING_TEST_H
#define THREADING_TEST_H

#include <iostream>
#include <future>

int return_int() {
    return 101;
}

int test_promise() {

    // std::promise<int> p = return_int;
    std::promise<int> p;
    p.set_value(6);
    std::future<int> fun = p.get_future();
    std::cout << fun.get();
}

#endif //THREADING_TEST_H
