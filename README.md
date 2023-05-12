# ModernCpp

## mutex 互斥锁

| API | C++ | 描述 |
| -- | -- | -- |
| mutex | C++11 | 基本互斥锁 |
| timed_mutex | C++11 | 带有超时功能的互斥锁 |
| recursive_mutex | C++11 | 可重入锁，能被同一线程递归锁定 |
| recursive_timed_mutex | C++11 | 带有超时功能的可重入锁 |
| shared_timed_mutex | C++14 | 提供共享互斥设施并带有超时功能 |
| shared_mutex | C++17 | 提供共享互斥设施 |


共享锁接口

| 方法 |
|--|
|lock_shared|
|try_lock_shared|
|unlock_shared|
|lock|
|try_lock|
|unlock|

## 通用互斥管理

| API | 版本 | 描述 |
|--|--|--|
| lock_guard | C++11 | 实现严格基于作用域的互斥体所有权包装器 |
| unique_lock | C++11 | 实现可移动的互斥体所有权包装器 |
| shared_lock | C++14 | 实现可移动的共享互斥体所有权封装器 |
| scoped_lock | C++17 | 用于多个互斥体的免死锁RAII 封装器 |

锁定策略

| 锁定策略 | 版本 | 说明 |
|--|--|--|
| defer_lock | C++11 | 不获得互斥的所有权 |
| try_to_lock | C++11 | 尝试获得互斥的所有权而不阻塞 |
| adopt_lock | C++11 | 假设调用方已拥有互斥的所有权 |

## 条件变量 线程间同步

| API | 版本 | 描述 |
| condition_variable | C++ 11 | 提供与 std::unique_lock 关联的条件变量 |
| condition_variable_any | C++ 11 |提供与任何锁类型关联的条件变量 |
| notify_all_at_thread_exit |C++ 11 | 安排到在此线程完全结束时对 notify_all 的调用 |
| cv_status | C++ 11 |列出条件变量上定时等待的可能结果 |


