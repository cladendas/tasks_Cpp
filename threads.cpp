#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Counter {
    int value = 0;
    std::mutex some_mutex;
public:
    void increment() {
        const std::lock_guard<std::mutex> lock(some_mutex);
        ++value;
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    Counter counter;
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&counter]() {
            for (int j = 0; j < 10; ++j) {
                counter.increment();
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}