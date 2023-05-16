#include <functional>
#include <iostream>

int foo(int a, int b, int c) {
    return a+b+c;
}

int main() {
    // std::function 包装了一个返回值为 int, 参数为 int 的函数
    std::function<int(int, int, int)> func = foo;

    int important = 10;
    std::function<int(int)> func2 = [&](int value) -> int {
        return 1+value+important;
    };

    std::cout << func(10, 10, 1) << std::endl;
    std::cout << func2(10) << std::endl;

    // bind绑定参数 placeholders占位符
    auto f = std::bind(foo, std::placeholders::_1, 10, 1);
    std::cout << f(10) << std::endl;
}