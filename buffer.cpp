#include <iostream>
#include <algorithm> // для std::copy

class Buffer {
    int* data_;
    std::size_t size_;
public:
    Buffer(std::size_t size) : size_(size), data_(new int[size]) {}
    ~Buffer() { delete[] data_; }
    
    // Конструктор копирования (ГЛУБОКОЕ КОПИРОВАНИЕ)
    Buffer(const Buffer& other) : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // Копирующий оператор присваивания
    Buffer& operator=(const Buffer& other) {
        if (this != &other) { // Защита от самоприсваивания
            // 1. Выделяем новую память и копируем данные
            int* new_data = new int[other.size_];
            std::copy(other.data_, other.data_ + other.size_, new_data);

            // 2. Освобождаем старую память
            delete[] data_;

            // 3. Присваиваем новые данные
            data_ = new_data;
            size_ = other.size_;
        }
        return *this;
    }

    // Перемещающий конструктор (ПЕРЕХВАТ РЕСУРСОВ)
    Buffer(Buffer&& other) noexcept : data_(other.data_), size_(other.size_) {
        // "Обнуляем" исходный объект
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // Перемещающий оператор присваивания (ПЕРЕХВАТ РЕСУРСОВ)
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            // 1. Освобождаем свои старые ресурсы
            delete[] data_;

            // 2. Забираем ресурсы у other
            data_ = other.data_;
            size_ = other.size_;

            // 3. Обнуляем other
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    void print() {
        std::cout << "size: " << size_ << '\n';
        std::cout << "address: " << static_cast<void*>(data_) << '\n';
    }
};

int main() {

    return 0;
}