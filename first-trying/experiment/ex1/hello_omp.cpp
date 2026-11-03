#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
#pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        int n = omp_get_num_threads();
// 加上原子锁保障整行打印不被打断，否则采用printf
#pragma omp critical
        {
            cout << "thread " << id << " of " << n << endl;
        }
    }
    return 0;
}