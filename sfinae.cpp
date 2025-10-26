#include <iostream>
#include <type_traits>

template<typename T>
void print_if_number(const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        std::cout << value << '\n';
    } else {
        std::cout << "Not a number" << '\n';
    }

}

int main() {
    print_if_number(42);
    print_if_number(3.14);
    print_if_number("hello");

    return 0;
}