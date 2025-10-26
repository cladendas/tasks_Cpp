#include <iostream>
#include <cctype> // std::tolower
#include <algorithm> // std::reverse
#include <thread>
#include <mutex>
#include <condition_variable>

void mystery(int* a, int* b) {
    a = b;
    *a = 5;
}

void task_11() {
    int x = 1, y = 2;
    mystery(&x, &y);
    std::cout << "x = " << x << ", y = " << y << std::endl;
    
    int* p = &x;
    int* q = &y;
    mystery(p, q);
    std::cout << "x = " << x << ", y = " << y << std::endl;
}

bool is_palindrome(const std::string& str) {
    std::string tmp;
    for(auto sym : str) {
        if (std::isalnum(sym)) {
            tmp += std::tolower(sym);
        }
    }

    for (size_t i = 0; i < tmp.size() / 2; i++)
    {
        if (tmp[i] != tmp[tmp.size() - 1 - i]) {
            return false;
        }
    }
    
    return true;


    ////////////////////////////////////////
    // std::string cleaned;
    
    // // Фильтруем и приводим к нижнему регистру
    // std::copy_if(str.begin(), str.end(), std::back_inserter(cleaned),
    //              [](char c) { return std::isalnum(static_cast<unsigned char>(c)); });
    // std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(),
    //               [](char c) { return std::tolower(static_cast<unsigned char>(c)); });
    
    // // Проверяем на палиндром
    // return std::equal(cleaned.begin(), cleaned.begin() + cleaned.size() / 2, 
    //                  cleaned.rbegin());
    ////////////////////////////////////////
    
}

void task_12() {
    std::cout << std::boolalpha;
    std::cout << is_palindrome("A man a plan a canal Panama") << '\n'; // true
    std::cout << is_palindrome("racecar") << '\n'; // true  
    std::cout << is_palindrome("hello") << '\n';   // false
    std::cout << std::noboolalpha;
}

class Base {
public:
    virtual void print() { std::cout << "Base" << std::endl; }
    void show() { std::cout << "Base show" << std::endl; }
};

class Derived : public Base {
public:
    void print() override { std::cout << "Derived" << std::endl; }
    void show() { std::cout << "Derived show" << std::endl; }
};

void task_13() {
    Base* b1 = new Base();
    Base* b2 = new Derived();
    Derived* d = new Derived();
    
    b1->print(); // Виртуальные функции (print): Вызываются по реальному типу объекта (dynamic dispatch)
    b1->show(); // Невиртуальные функции (show): Вызываются по типу указателя/ссылки (static dispatch)
    b2->print();
    b2->show(); 
    d->print(); 
    d->show();
    
    delete b1; 
    delete b2; 
    delete d;
}

template<typename T>
void swap_values(T& a, T& b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

void task_14() {

    std::string a = "aaa";
    std::string b = "bbb";
    swap_values(a, b);
    std::cout << a << " - " << b << '\n';

    int x = 1;
    int y = 2;
    swap_values(x, y);
    std::cout << x << " - " << y << '\n';

    char sym_0 = 'A';
    char sym_1 = 'B';
    swap_values(sym_0, sym_1);

    std::cout << sym_0 << " - " << sym_1 << '\n';
}

#include <limits>
class Calculator {
public:
    int add(int a, int b) {
        long long result = static_cast<long long>(a) + b;
        if (result > std::numeric_limits<int>::max() || 
            result < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Addition result out of int range");
        }
        return static_cast<int>(result);
    }

    int subtract(int a, int b) {
        long long result = static_cast<long long>(a) - b;
        if (result > std::numeric_limits<int>::max() || 
            result < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Subtraction result out of int range");
        }
        return static_cast<int>(result);
    }

    int multiply(int a, int b) {
        if (a > 0) {
            if (b > 0) {
                if (a > std::numeric_limits<int>::max() / b) throw std::overflow_error("Multiplication result out of int range");
            } else {
                if (b < std::numeric_limits<int>::min() / a) throw std::overflow_error("Multiplication result out of int range");
            }
        } else {
            if (b > 0) {
                if (a < std::numeric_limits<int>::min() / b) throw std::overflow_error("Multiplication result out of int range");
            } else {
                if (a != 0 && b < std::numeric_limits<int>::max() / a) throw std::overflow_error("Multiplication result out of int range");
            }
        }
        return a * b;
    }

    double divide(int a, int b) {
        if (b == 0) {
            throw std::invalid_argument("Division by zero"); 
        }
        // Преобразуем к double до деления для точности
        return static_cast<double>(a) / b;
    }
};


void task_15() {
    try {
        Calculator calc = Calculator();
        // std::cout << calc.add(INT_MAX, INT_MAX) << '\n';
        // std::cout << calc.subtract(INT_MIN, INT_MAX) << '\n';
        // std::cout << calc.multiply(INT_MAX, INT_MAX) << '\n';
        // std::cout << calc.divide(INT_MAX, 0) << '\n';


    } catch (const std::range_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void use() { std::cout << "Resource used\n"; }
};


void task_16() {
    /*
    Задача 16: Умные указатели и владение памятью
Условие: Дан код с сырыми указателями. 
Перепишите его, используя умные указатели (unique_ptr, shared_ptr), 
чтобы избежать утечек памяти и сделать код безопасным.
    */

    std::unique_ptr<Resource> res1 { std::make_unique<Resource>() };
    std::shared_ptr<Resource> res2 { std::make_shared<Resource>() };
    std::shared_ptr<Resource> res3 { res2 };
    
    res1->use();
    res2->use();
    res3->use();
}

#include <unordered_set>
std::vector<int> get_unique_elements(const std::vector<int>& input) {
    std::unordered_set<int> tmp_unordered_set;
    std::vector<int> result;
    for (auto &&i : input) {
        if (!tmp_unordered_set.count(i)) {
            result.emplace_back(i);
            tmp_unordered_set.insert(i);
        }
    }
    return result;
}

void task_17() {
/*
Задача 17: Работа с STL контейнерами
Условие: Напишите функцию, которая принимает вектор целых чисел и возвращает новый вектор, 
содержащий только уникальные элементы из исходного вектора в том порядке, в котором они первый раз встречаются.
*/

    std::vector<int> input = {1, 2, 3, 2, 4, 1, 5, 3};
    std::vector<int> result = get_unique_elements(input);
    // result должен быть: {1, 2, 3, 4, 5}

    for (auto &&i : result)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

class Test {
public:
    Test() { std::cout << "Default constructor\n"; }
    Test(const Test& other) { std::cout << "Copy constructor\n"; }
    Test(Test&& other) { std::cout << "Move constructor\n"; }
    Test& operator=(const Test& other) { 
        std::cout << "Copy assignment\n"; 
        return *this;
    }
    Test& operator=(Test&& other) { 
        std::cout << "Move assignment\n"; 
        return *this;
    }
};

Test createTest() {
    return Test();
}

void task_18() {
/*
Задача 18: Конструкторы и операторы присваивания
Жду ваше объяснение вывода программы! Для каждого теста объясните, какой конструктор/оператор вызывается и почему.

Особое внимание на Test 5 и Test 6 - там может быть интересное поведение из-за оптимизаций компилятора.

=== Test 1 ===
Default constructor
=== Test 2 ===
Copy assignment
=== Test 3 ===
Move assignment
=== Test 4 ===
Copy assignment
=== Test 5 ===
Default constructor
Move assignment
=== Test 6 ===
Default constructor
*/

    std::cout << "=== Test 1 ===\n";
    Test t1;
    
    std::cout << "=== Test 2 ===\n";
    Test t2 = t1; //это инициализация, а не присваивание! Вызывается конструктор копирования.
    
    std::cout << "=== Test 3 ===\n";
    Test t3 = std::move(t1); //инициализация с перемещением, вызывается перемещающий конструктор.
    
    std::cout << "=== Test 4 ===\n";
    t2 = t3; //здесь происходит присваивание, а не инициализация. Вызывается перемещающий оператор присваивания.
    
    std::cout << "=== Test 5 ===\n";
    t3 = createTest();
    
    std::cout << "=== Test 6 ===\n";
    Test t4 = createTest(); //благодаря RVO (Return Value Optimization) компилятор может исключить лишние копирования/перемещения и создать объект напрямую в t4.

}

std::vector<std::string> filter_strings_by_length(const std::vector<std::string>& strings, size_t min_length) {
    std::vector<std::string> result;
    std::copy_if(strings.begin(), strings.end(), std::back_inserter(result), [min_length](auto& str){
        return str.size() > min_length;
    });
    return result;

    ////////////////////////////////////////
    // auto filtered = strings | std::views::filter([min_length](const std::string& str) {
    //     return str.size() > min_length;
    // });
    // return {filtered.begin(), filtered.end()};
    ////////////////////////////////////////
}

void task_19() {
/*
Задача 19: Лямбда-выражения и алгоритмы STL
Условие: Напишите функцию, которая принимает вектор строк и возвращает новую вектор, 
содержащий только те строки, длина которых больше заданного значения. 
Используйте алгоритмы STL и лямбда-выражения.
*/
    std::vector<std::string> input = {"hello", "I", "am", "learning", "C++"};
    auto result = filter_strings_by_length(input, 3);

    for (auto &&i : result)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    // result: {"hello", "learning", "C++"}

}


std::mutex g_mutex;
std::condition_variable g_cv;
std::queue<int> g_queue;
bool g_finished = false;

void producer() {
    for (int i = 1; i <= 100; ++i) {
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            g_queue.push(i);
        }
        g_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_finished = true;
    }
    g_cv.notify_one();
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(g_mutex);
        g_cv.wait(lock, []() { return !g_queue.empty() || g_finished; });
        
        if (g_finished && g_queue.empty()) break;
        
        while (!g_queue.empty()) {
            int value = g_queue.front();
            g_queue.pop();
            lock.unlock(); // Освобождаем мьютекс во время вывода
            std::cout << "Consumed: " << value << std::endl;
            lock.lock();
        }
    }
}

void task_20() {
/*
Задача 20: Базовые многопоточность
Условие: Напишите программу, которая создает два потока. 
Первый поток генерирует числа от 1 до 100, второй поток выводит эти числа в консоль. 
Используйте механизмы синхронизации для безопасного обмена данными.

Требования:
Поток-производитель генерирует числа
Поток-потребитель выводит числа
Синхронизация с помощью мьютексов и условных переменных
Корректное завершение потоков
*/

    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();

}

int main() {
    // task_11();
    // task_12();
    // task_13();
    // task_14();
    // task_15();
    // task_16();
    // task_17();
    // task_18();
    // task_19();
    task_20();

}