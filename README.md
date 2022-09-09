### 介绍condition_variable的使用
#### condition_variable 条件变量一般用法是：线程thread_A等待某个条件被挂起，直到线程thread_B设置了这个条件，通知条件变量，thread_A被唤醒。
```c++
#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void Worker() {
    std::unique_lock<std::mutex> lk(m);
    
    // wait 
    cv.wait(lk, []{reutrn ready;});
    
    std::cout << "Worker thread is processing data\n";
    data += "after processing\n";
    
    processed = true;
    std::cout << "Worker thread signal data processing completed\n";
    
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

int main() {
    std::thread worker(Worker);
    
    data = "Example data";
    // send data to worker thread
    {
        std::unique_lock<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signal data ready for processing\n";
    }
    cv.notify_one();
    
    // wait for worker
    {
        std::unique_lock lk(m);
        vc.wait(lk, []{ reutrn processed;});
    }
    std::cout << "Back in main(), data = " << data;
    
    worker.join();
    
    return 0;
}
```
#### Output:
```text
main() signals data ready for processing
Worker thread is processing data
Worker thread signals data processing completed
Back in main(), data = Example data after processing
```