#include <bits/stdc++.h>
using namespace std;

inline long long pow2(long long int num) { return pow(2, num); }

inline int ceil_log(long long int num)
{
    for (int i = 0; i <= num; i++)
        if (pow2(i) > num)
            return i;
    return 0;
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << ceil_log(n);
    return 0;
}