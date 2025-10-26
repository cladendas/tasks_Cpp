#include <string>
#include <cstdio>
#include <stdexcept>
#include <utility>

class File {
public:
    File(const std::string& filename, const std::string& mode) {
        handle_ = std::fopen(filename.c_str(), mode.c_str());
        if (!handle_) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }

    ~File() {
        if (handle_) {
            std::fclose(handle_);
        }
    }
    
    // Запрещаем копирование
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    
    // Перемещающий конструктор
    File(File&& other) noexcept : handle_(other.handle_) {
        other.handle_ = nullptr; // Забираем владение
    }

    // Перемещающий оператор присваивания
    File& operator=(File&& other) noexcept {
        if (this != &other) {
            // Освобождаем текущий ресурс
            if (handle_) {
                std::fclose(handle_);
            }
            // Забираем ресурс у other
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
    
    size_t read(void* buffer, size_t size) {
        if (!handle_) {
            throw std::runtime_error("File is not open");
        }
        return std::fread(buffer, 1, size, handle_);
    }

    size_t write(const void* buffer, size_t size) {
        if (!handle_) {
            throw std::runtime_error("File is not open");
        }
        return std::fwrite(buffer, 1, size, handle_);
    }

    bool is_open() const { return handle_ != nullptr; }
    int seek(long offset, int origin) {
        return std::fseek(handle_, offset, origin);
    }
    
private:
    FILE* handle_;
};

int main() {

    return 0;
}