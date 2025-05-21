using System;
using System.Diagnostics;
using System.Numerics;

class MatrixMultiplication
{
    static void Main()
    {
        Console.WriteLine("Лабораторная работа по умножению матриц");
        Console.WriteLine("Автор: Китаев Максим Денисович, группа АИСа-о24");

        int size = 1024;
        Complex[,] matrixA = GenerateRandomMatrix(size);
        Complex[,] matrixB = GenerateRandomMatrix(size);

        var stopwatch = Stopwatch.StartNew();
        Complex[,] result = MultiplyMatrices(matrixA, matrixB);
        stopwatch.Stop();

        double time = stopwatch.Elapsed.TotalSeconds;
        double mflops = (2 * Math.Pow(size, 3)) / (time * 1e6);

        Console.WriteLine($"Время выполнения: {time} сек");
        Console.WriteLine($"Производительность: {mflops} MFLOPS");
    }

    static Complex[,] GenerateRandomMatrix(int size)
    {
        Random rand = new Random();
        Complex[,] matrix = new Complex[size, size];

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                float real = (float)rand.NextDouble();
                float imag = (float)rand.NextDouble();
                matrix[i, j] = new Complex(real, imag);
            }
        }
        return matrix;
    }

    static Complex[,] MultiplyMatrices(Complex[,] a, Complex[,] b)
    {
        int size = a.GetLength(0);
        Complex[,] result = new Complex[size, size];

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Complex sum = Complex.Zero;
                for (int k = 0; k < size; k++)
                {
                    sum += a[i, k] * b[k, j];
                }
                result[i, j] = sum;
            }
        }
        return result;
    }
}