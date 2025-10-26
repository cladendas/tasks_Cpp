#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

class Matrix {
    std::vector<std::vector<double>> data;
public:
    Matrix(size_t rows, size_t cols) : data(rows, std::vector<double>(cols)) {}

    Matrix(Matrix&& other) noexcept : data(std::move(other.data)) {}

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    Matrix(const Matrix& other) : data(other.data) {}

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }
    
    Matrix transpose() const {
        Matrix result(cols(), rows());
        for (size_t i = 0; i < rows(); ++i)
            for (size_t j = 0; j < cols(); ++j)
                result[j][i] = (*this)[i][j];
        return result;
    }

    // Дополнительная оптимизация - транспонирование на месте
    void transpose_in_place() {
        // Только для квадратных матриц
        if (rows() != cols()) return;
        
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = i + 1; j < cols(); ++j) {
                std::swap(data[i][j], data[j][i]);
            }
        }
    }
    
    size_t rows() const { return data.size(); }
    size_t cols() const { return data.empty() ? 0 : data[0].size(); }
    
    std::vector<double>& operator[](size_t i) { return data[i]; }
    const std::vector<double>& operator[](size_t i) const { return data[i]; }
};

int main() {

    return 0;
}