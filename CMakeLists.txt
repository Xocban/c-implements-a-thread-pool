cmake_minimum_required(VERSION 3.21)
project(threading)

set(CMAKE_CXX_STANDARD 14)

add_executable(threading main.cpp test/test_mutex.cpp test/test_mutex.h test/thread_safe_stack.cpp test/thread_safe_stack.h test/test_function.cpp test/test_function.h test/threadsafe_queue.cpp test/threadsafe_queue.h test/test.h)
