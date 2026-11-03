#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main()
{
    const long N = 1000000000L;

    vector<double> a(N, 1.0);

    // 串行版本
    double sum_serial = 0.0;
    double t0 = omp_get_wtime();
    for (long i = 0; i < N; i++)
    {
        sum_serial += a[i];
    }
    double t1 = omp_get_wtime();

    // 并行版本
    double sum_parallel = 0.0;
    double t2 = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum_parallel)
    for (long i = 0; i < N; i++)
    {
        sum_parallel += a[i];
    }
    double t3 = omp_get_wtime();

    cout << "串行: sum = " << sum_serial << ", 用时 = " << (t1 - t0) << " s\n";
    cout << "并行: sum = " << sum_parallel << ", 用时 = " << (t3 - t2) << " s" << ", 线程数 = " << omp_get_max_threads() << "\n";
    cout << "加速比: " << (t1 - t0) / (t3 - t2) << "x\n";

    return 0;
}