#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> count = {0};

struct A {
    float x;
    int y;
    long long z;
};

int main() {
    std::cout << std::boolalpha << count.is_lock_free() << std::endl;
    std::thread t1([](){
        count.fetch_add(1);
    });
    std::thread t2([](){
        count++;        // 等价于 fetch_add
        count += 1;     // 等价于 fetch_add
    });
    t1.join();
    t2.join();
    std::cout << count << std::endl;

    // 检查自定义类型是否支持原子操作
    std::atomic<A> a;  // 不支持 直接编译不通过
    // std::cout << std::boolalpha << a.is_lock_free() << std::endl;
    return 0;
}