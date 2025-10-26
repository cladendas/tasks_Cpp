#include <iostream>

template<typename T>
class Simple_uptr {
    T* _ptr;
public:
    explicit Simple_uptr(T* ptr): _ptr(ptr) {}
    ~Simple_uptr() {
        delete _ptr;
    }

    // Запрещаем копирование
    Simple_uptr(const Simple_uptr&) = delete;
    Simple_uptr& operator=(const Simple_uptr&) = delete;

    // перемещающий конструктор
    Simple_uptr(Simple_uptr&& other) noexcept : _ptr(other._ptr) {
        other._ptr = nullptr; // "Забираем" указатель у other
    }

    // перемещающий оператор присваивания
    Simple_uptr& operator=(Simple_uptr&& other) noexcept {
        // Защита от самоприсваивания (x = std::move(x))
        if (this != &other) {
            delete _ptr;     // Освобождаем старые ресурсы
            _ptr = other._ptr; // Забираем новые
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Перегрузка оператора разыменования *
    T& operator*() const {
        return *_ptr;
    }

    // Перегрузка оператора стрелки ->
    T* operator->() const {
        return _ptr;
    }

    T* get() const {
        return _ptr;
    }

};

int main() {
    return 0;
}