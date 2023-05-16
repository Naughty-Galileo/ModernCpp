#include <iostream>

template <typename... Ts>
void magic(Ts... args) {
    std::cout << sizeof...(args) << std::endl;
}

// 1、递归模板函数
template<typename T>
void MyPrint(T value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Ts>
void MyPrint(T value, Ts... args) {
    std::cout << value << " ";
    MyPrint(args...); // ...容易忘记
}

// c++17增加变参模板展开
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) printf2(t...);
}

// 初始化列表展开
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    (void) std::initializer_list<T>{
        ( [&args] {
        std::cout << args << std::endl;
    }(), value)...
    };
}


int main() {
    magic();
    magic(1);
    magic(1, 1.2, "");

    MyPrint(1, 2.2, "string");

    printf2(1, 2.2, "string");

    printf3(1, 2.2, "string");
}
