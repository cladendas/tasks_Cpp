#include <iostream>
#include <vector>
#include <utility>

template<typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity) : data_(capacity), capacity_(capacity), head_(0), tail_(0), full_(false) {}

    void push(const T& item) {
        data_[head_] = item;
        
        if (full_) {
            tail_ = (tail_ + 1) % capacity_;
        }
        
        head_ = (head_ + 1) % capacity_;
        full_ = (head_ == tail_);
    }

    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return data_[(tail_ + index) % capacity_];
    }

    const T& operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return data_[(tail_ + index) % capacity_];
    }

    size_t size() const {
        if (full_) return capacity_;
        if (head_ >= tail_) return head_ - tail_;
        return capacity_ + head_ - tail_;
    }

    size_t capacity() const { return capacity_; }

    bool empty() const { return !full_ && (head_ == tail_); }
    bool full() const { return full_; }

    RingBuffer(RingBuffer&& other) noexcept
        : data_(std::move(other.data_)),
          capacity_(other.capacity_),
          head_(other.head_),
          tail_(other.tail_),
          full_(other.full_) {
        other.capacity_ = 0;
        other.head_ = other.tail_ = 0;
        other.full_ = false;
    }


    RingBuffer& operator=(RingBuffer&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            capacity_ = other.capacity_;
            head_ = other.head_;
            tail_ = other.tail_;
            full_ = other.full_;
            
            other.capacity_ = 0;
            other.head_ = other.tail_ = 0;
            other.full_ = false;
        }
        return *this;
    }

private:
    std::vector<T> data_;
    size_t capacity_;
    size_t head_;  // индекс для следующей записи
    size_t tail_;  // индекс самого старого элемента
    bool full_;
};

int main() {

    return 0;
}