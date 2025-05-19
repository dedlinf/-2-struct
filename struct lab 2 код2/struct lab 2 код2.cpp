#include <iostream>
#include <complex>
#include <vector>
#include <random>
#include <chrono>
#include <stdexcept>
#include <locale>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

constexpr int N = 512; 

// Функция для установки локали для поддержки русского языка
void setRussianLocale() {
    
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
#else

    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    std::wcin.imbue(std::locale());
}

// Функция для умножения комплексных матриц
void matrixMultiply(const std::vector<std::complex<float>>& A,
    const std::vector<std::complex<float>>& B,
    std::vector<std::complex<float>>& C) {
    if (A.size() != N * N || B.size() != N * N || C.size() != N * N) {
        throw std::invalid_argument("Matrix sizes are incorrect");
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::complex<float> sum(0.0f, 0.0f);
            for (int k = 0; k < N; ++k) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

int main() {
    
    setRussianLocale();

    
    std::cout << "Группа: АИС-020303-2024\n";
    std::cout << "Студент: Киtaев Максим Денисович\n\n";

    
    std::vector<std::complex<float>> A(N * N);
    std::vector<std::complex<float>> B(N * N);
    std::vector<std::complex<float>> C(N * N);

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);

    
    for (auto& elem : A) {
        elem = { dist(gen), dist(gen) };
    }
    for (auto& elem : B) {
        elem = { dist(gen), dist(gen) };
    }

    // 4. Замер времени выполнения
    auto start = std::chrono::high_resolution_clock::now();

    
    matrixMultiply(A, B, C);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // 6. Вычисление производительности
    const double operations = 8.0 * N * N * N;  // 8N^3 операций для комплексных чисел
    const double gflops = (operations / elapsed.count()) * 1e-9;

    // 7. Вывод результатов
    std::cout << "Умножение комплексных матриц (нативный C++)\n";
    std::cout << "========================================\n";
    std::cout << "Размер матриц:      " << N << " x " << N << "\n";
    std::cout << "Время выполнения:   " << elapsed.count() << " сек\n";
    std::cout << "Всего операций:     " << operations << "\n";
    std::cout << "Производительность: " << gflops << " GFlops\n";
    std::cout << "========================================\n";

    // 8. Проверка результата (выводим один элемент для проверки)
    std::cout << "Элемент C[0][0] = " << C[0] << "\n";

    return 0;
}
