# ModernCpp

## 并发编程
### mutex 互斥锁

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

### 通用互斥管理

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

### 条件变量 线程间同步

| API | 版本 | 描述 |
| condition_variable | C++ 11 | 提供与 std::unique_lock 关联的条件变量 |
| condition_variable_any | C++ 11 |提供与任何锁类型关联的条件变量 |
| notify_all_at_thread_exit |C++ 11 | 安排到在此线程完全结束时对 notify_all 的调用 |
| cv_status | C++ 11 |列出条件变量上定时等待的可能结果 |

### 原子操作 将原子类型读写操作从一组指令最小化到单个CPU指令
- 整数和浮点数的原子类型提供了fetch_add,fetch_sub,并重载++，--，+，-
- std::atomic<T>::is_lock_free检查是否支持原子操作



## 语言可用性的强化
### [变长参数模板](./Variable_length_parameter_template.cpp)

- 递归模板函数
- 变参模板展开
- 初始化列表展开

### [非类型模板参数推导](./Non_type_parameter_template_derivation.cpp)


## 语言运行期强化
### [函数对象包装器](./function_demo.cpp)
- std::function
- std::bind 和 std::placeholder

### [右值引用](./forward_demo.cpp)
- 右值
- 右值引用
- 移动语义
- 完美转发

## 正则表达式
### 特殊字符

| 特殊字符 | 描述 |
|--|--|
| $ | 匹配输入字符串的结尾位置 |
| (,) | 标记一个子表达式的开始和结束位置 |
| * | 匹配前面的子表达式零次或多次 |
| + | 匹配前面的子表达式一次或多次 |
| . | 匹配除换行符之外的任何单字符 |
| ? | 匹配前面的子表达式零次或一次 |



