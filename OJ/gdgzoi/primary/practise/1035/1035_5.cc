#include <iostream>
using namespace std;
long long q[(int)1e6 + 1];
int main()
{
    int n;
    cin >> n;
    long long x = 1, y = 1, z = 1, s = 1;
    long long tail = 2;
    long long tmp1, tmp2, tmp3, tmp4, tmp5;
    q[1] = 1;
    while (tail <= n)
    {
        tmp1 = q[x] * 2;
        tmp2 = q[y] * 3;
        tmp4 = q[z] * 5;
        tmp5 = q[s] * 7;
        tmp3 = min(tmp1, min(tmp2, min(tmp4, tmp5)));
        if (tmp1 == tmp3)
            x++;
        if (tmp2 == tmp3)
            y++;
        if (tmp4 == tmp3)
            z++;
        if (tmp5 == tmp3)
            s++;
        if (tmp3 == q[tail - 1])
            continue;
        q[tail] = tmp3;
        tail++;
    }
    cout << q[n];
    return 0;
}