#include <iostream>
#include <complex>
#include <random>
#include <chrono>
#include <vector>
#include <Windows.h>

using namespace std;
using namespace chrono;

typedef complex<float> Complex;


void printAuthorInfo() {
    cout << "Автор: Китаев Максим Денисович, группа АИСа-о24" << endl;
    cout << "Лабораторная работа: Умножение комплексных матриц" << endl << endl;
}


void initializeRandomMatrix(vector<Complex>& matrix, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < size * size; ++i) {
        matrix[i] = Complex(dist(gen), dist(gen));
    }
}


void classicMultiply(const vector<Complex>& A, const vector<Complex>& B, vector<Complex>& C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Complex sum(0.0f, 0.0f);
            for (int k = 0; k < size; ++k) {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }
}

int main() {
    
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "Russian");

    const int N = 1024; 
    vector<Complex> A(N * N);
    vector<Complex> B(N * N);
    vector<Complex> C(N * N);

    
    cout << "Инициализация матриц..." << endl;
    initializeRandomMatrix(A, N);
    initializeRandomMatrix(B, N);

   
    printAuthorInfo();

    
    cout << "Выполняется умножение матриц " << N << "x" << N << "..." << endl;
    auto start = high_resolution_clock::now();
    classicMultiply(A, B, C, N);
    auto end = high_resolution_clock::now();

    double time = duration_cast<duration<double>>(end - start).count();
    double mflops = (2.0 * N * N * N) / (time * 1e6); 

    
    cout << "\nРезультаты:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Размер матрицы:          " << N << "x" << N << endl;
    cout << "Затраченное время:       " << time << " секунд" << endl;
    cout << "Производительность:      " << mflops << " MFLOPS" << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}