#pragma GCC optimize("O2,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")

#include <immintrin.h>
#include <emmintrin.h> //sse2
#include <iostream>

const int MAX_N = 2e5 + 10;

int tot = 0;
int real_height[MAX_N];
__m256 height[MAX_N];
__m256 res;
int n, q;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> q;

    for (int i = 0; i < n; i++)
    {
        float *tmp;
        std::cin >> *tmp;
        real_height[i] = *tmp;
        height[i] = _mm256_load_ps(tmp);
    }

    for (int _q = 0; _q < q; _q++)
    {
        float *x, *y;
        std::cin >> *x >> *y;
        __m256 xx = _mm256_load_ps(x);
        __m256 yy = _mm256_load_ps(y);

        res = _mm256_add_ps(yy, -height[(int)*x]);
        for (int i = *x - 1; i >= 1 and real_height[i] < *y; i--)
            res += _mm256_add_ps(yy, -height[i]);
        for (int i = *x + 1; i <= n and real_height[i] < *y; i++)
            res += _mm256_add_ps(yy, -height[i]);

        std::cout << (int *)&res << "\n";
    }
    return 0;
}