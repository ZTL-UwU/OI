#include <iostream>
using namespace std;
int q[(int)1e6 + 1];
int main()
{
    int a, n;
    cin >> a >> n;
    int x = 1, y = 1;
    int tail = 2;
    int tmp1, tmp2, tmp3;
    q[1] = a;
    while (tail <= n)
    {
        tmp1 = q[x] * 2 + 1;
        tmp2 = q[y] * 3 + 1;
        tmp3 = min(tmp1, tmp2);
        if (tmp1 <= tmp2)
            x++;
        else
            y++;
        if (tmp3 == q[tail - 1])
            continue;
        q[tail] = tmp3;
        tail++;
    }
    cout << q[n];
    return 0;
}