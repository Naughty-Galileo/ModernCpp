#include <iostream>
#include <atomic>
#include <thread>
#include <cmath>
#include <vector>
#include <chrono>

class MyMutex {
public:
    void lock() {
        bool expected = false;
        while (!_lock.compare_exchange_weak(expected, true)) {
            expected = false;
            std::this_thread::yield();
        }
    }

    void unlock() {
        _lock.store(false);
    }

private:
    std::atomic<bool> _lock = ATOMIC_VAR_INIT(false);
};




MyMutex mtx;
static const int MAX = 10e8;
static double sum = 0;

void worker(int min, int max) {
    double cur = 0;
    for (int i = min; i <= max; i++) {
        cur += sqrt(i);
    }
    mtx.lock();
    sum += cur;
    mtx.unlock();
}


void concurrent_task(int min, int max) {
  auto start_time = std::chrono::steady_clock::now();

  unsigned concurrent_count = std::thread::hardware_concurrency();
  std::vector<std::thread> threads; 
  min = 0;
  sum = 0;

  for (int t = 0; t < concurrent_count; t++) {
    int range = max / concurrent_count * (t + 1);
    threads.push_back(std::thread(worker, min, range));
    min = range + 1;
  }

  for (int i = 0; i < threads.size(); i++) {
    threads[i].join();
  }

  auto end_time = std::chrono::steady_clock::now();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << std::endl;
}

void serial_task(int min, int max) {
  auto start_time = std::chrono::steady_clock::now();
  sum = 0;
  worker(0, MAX);
  auto end_time = std::chrono::steady_clock::now();
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
  std::cout << "Serail task finish, " << ms << " ms consumed, Result: " << sum << std::endl;
}


int main() {
    serial_task(0, MAX);
    concurrent_task(0, MAX);
    return 0;
}




