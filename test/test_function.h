//
// Created by River X on 2022/9/6.
//

#ifndef THREADING_TEST_FUNCTION_H
#define THREADING_TEST_FUNCTION_H
#include<mutex>
#include<iostream>
#include<thread>
#include<condition_variable>


class test_function {
private:
    std::mutex m;
public:
    void print_ ();
    void print__ ();
    void run ();
};

extern std::mutex m;

void print_ ();
void print__ ();
void run ();


#endif //THREADING_TEST_FUNCTION_H
