#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>
using namespace std;

const int N = 50000000;
// 或者直接vector<double> a(N,1.0);
vector<double> a, b, c;

int main()
{
    a.assign(N, 1.0);
    b.assign(N, 2.0);
    c.assign(N, 0.0);

    // 串行计算
    double t1 = omp_get_wtime();
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }
    double ts = omp_get_wtime() - t1;

    omp_set_num_threads(4);
    double t3 = omp_get_wtime();
#pragma omp parallel
#pragma omp for
    // 这里因为不会干扰共同的参数,所以不用采用 #pragma omp parallel for reduction(+ : x)这样的形式
    for (int i = 0; i < N; i++)
    {
        a[i] = b[i] + c[i];
    }
    double tp = omp_get_wtime() - t3;

#pragma omp critical
    {
        cout << fixed << setprecision(3);
        cout << "serial  " << ts << endl;
        cout << "parallel  " << tp << endl;
        cout << "speedup  " << ts / tp << endl;
    }

    return 0;
}