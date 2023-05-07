#include <mutex>
#include <thread>
#include <assert.h>
#include <iostream>

using namespace std;

void func(int num) {
    assert(num > 0);

    // get_id()
    cout << this_thread::get_id() << " hello !" << endl;

    // sleep_for()  
    // sleep_until()
    this_thread::sleep_for(chrono::seconds(num));

    // yield 通常用在自己的主要任务已经完成的时候，此时希望让出处理器给其他任务使用
}

void Init() {
    cout << "Initialing..." << endl;
}

void worker(once_flag* flag) {
    call_once(*flag, Init);
}


int main(int argc, char*argv[]) {
    
    // 1、thread简单用法
    thread myThread(func, 5);

    // joinable
    if (myThread.joinable()) {
        myThread.join();
    }

    // hardware_concurrency
    unsigned int num = myThread.hardware_concurrency();
    cout << "The number of hardware thread contexts: " << num << endl;

    // 2、一次调用 有些任务只希望执行一次 <mutex> 互斥
    once_flag flag;
    thread init_1(worker, &flag);
    thread init_2(worker, &flag);
    thread init_3(worker, &flag);
    init_1.join();
    init_2.join();
    init_3.join();
    
    return 0;
}