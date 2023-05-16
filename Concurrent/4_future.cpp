#include <cmath>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

static const int MAX = 10e8;
static double sum = 0;

void worker(int min, int max) {
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }
}

class Worker {
public:
    Worker(int min, int max) : mMin(min), mMax(max) {}
    double work() {
        mResult = 0;
        for (int i = mMin; i <= mMax; i++) {
            mResult += sqrt(i);
        }
        return mResult;
    }

    double getRsult() {
        return mResult;
    }

private:
    int mMin;
    int mMax;
    double mResult;
};


double concurrent_worker(int min, int max) {
  double sum = 0;
  for (int i = min; i <= max; i++) {
    sum += sqrt(i);
  }
  return sum;
}

void concurrent_task(int min, int max, promise<double>* result) {
  vector<future<double>> results; // 存储结果

  unsigned concurrent_count = thread::hardware_concurrency();
  min = 0;

  for (int i = 0; i < concurrent_count; i++) { // 根据核数创建线程数量

    packaged_task<double(int, int)> task(concurrent_worker); // 包装任务 通过future对象获取返回值
    
    results.push_back(task.get_future()); // 获取任务关联的future 存入集合中

    int range = max / concurrent_count * (i + 1);

    thread t(std::move(task), min, range); // 执行任务传入参数
    t.detach();

    min = range + 1;
  }

  cout << "threads create finish" << endl;
  double sum = 0;
  for (auto& r : results) {
    sum += r.get(); // future .get获取每个任务的返回值
  }
    //   return sum;
    
    result->set_value(sum);
    cout << "concurrent_task finish" << endl;
}


int main() {
    sum = 0;
    // async 启动任务 返回std::future对象用来存储异步任务的执行结果
    // 启动新线程/同步 的方式由编译器决定
    
    // launch::async 有两个常量 可以指定为异步执行任务
    // async：运行新线程，以异步执行任务
    // deferred：调用方线程上第一次请求其结果时才执行任务，即惰性求值
    // auto f2 = async(launch::async, worker, 0, MAX);

    auto f1 = async(worker, 0, MAX);

    // 以对象的方法指定异步任务
    Worker w(0, MAX);
    auto f3 = async(&Worker::work, &w);

    cout << "Async task triggered" << endl;

    f1.wait();
    cout << "Async task finish, result: " << sum << endl;

    f3.wait();
    cout << "Async task in class finish, result: " << w.getRsult() << endl;

    // packaged_task 包装任务
    // 绑定到一个函数或者可调用对象上
    // 当它被调用时，它就会调用其绑定的函数或者可调用对象。并且，可以通过与之相关联的future来获取任务的结果
    // double r = concurrent_task(0, MAX);
    // cout << "Async task packaged_task, result: " << r << endl;

    // promise与future配对使用  将返回结果和任务结束两个事情分开
    promise<double> sum;
    concurrent_task(0, MAX, &sum);

    cout << "Async task packaged_task promise, result: " << sum.get_future().get() << endl;
}
