#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int ns[] = {1, 2, 4, 8};
    for (int i = 0; i < 4; i++)
    {
        omp_set_num_threads(ns[i]);
        cout << "---设置" << ns[i] << "个线程---" << endl;
#pragma omp parallel
#pragma omp critical
        {
            cout << "thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << endl;
        }
    }
    return 0;
}