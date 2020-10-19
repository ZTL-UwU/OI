#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

#include <dbg.h>

const int MAX_LOG = 5e1;
long long int choose[MAX_LOG];
long long int n, k;

inline long long pow2(long long int num)
{
    return pow(2, num);
}

inline int ceil_log(long long int num)
{
    for (int i = 0; i <= num; i++)
        if (pow2(i) > num)
            return i;
    return 0;
}

int main()
{
    std::cin >> n >> k;

    long long int layer = ceil_log(k);
    return 0;
}