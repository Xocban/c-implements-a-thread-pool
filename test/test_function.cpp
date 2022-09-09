//
// Created by River X on 2022/9/6.
//

#include "test_function.h"

void test_function::print_() {
    std::lock_guard<std::mutex> guard(m);
    print__();
    std::cout << "1\n";
}

void test_function::print__() {
    std::lock_guard<std::mutex> guard(m);
    std::cout << "2\n";
}

void test_function::run() {
    // std::thread(print_).join();
}

/*
 * TODO: 以下情况会产生死锁
 */

std::mutex m;

void print_() {
    std::lock_guard<std::mutex> guard(m);
    print__();
    std::cout << "1\n";
}

void print__() {
    std::lock_guard<std::mutex> guard(m);
    std::cout << "2\n";
}

void run() {
    std::thread(print_).join();
}