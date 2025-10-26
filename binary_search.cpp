#include <iostream>
#include <vector>

int binary_search(const std::vector<int>& data, int target) {

    if (data.empty()) {
        return -1;
    }

    size_t start = 0;
    size_t end = data.size() - 1;
    size_t mid = -1;

    while(start <= end) {
        mid = start + (end - start) / 2; // Эта формула математически эквивалентна, но исключает риск переполнения

        if (data[mid] == target) {
            return static_cast<int>(mid);
        } else if (data[mid] < target) {
            start = mid + 1;
        } else if (data[mid] > target) {
            end = mid - 1;
        }
    }

    return -1;
}

int main() {

    std::vector<int> vec {1,2,3,4,5};

    int result = binary_search(vec, 3);

    std::cout << result << '\n';

    return 0;
}