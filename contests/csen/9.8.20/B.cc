#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
struct data
{
    int x;
    int y;
};
int n, k, w1, w2;
data coord[5000];
int main()
{
    cin >> n >> k >> w1 >> w2;
    if (w1 * 2 <= w2)
    {
        cout << n * 2;
        return 0;
    }
    for (int i = 0; i < k; i++)
        cin >> coord[i].x >> coord[i].y;
    if (n <= 3)
    {
        cout << (n - 2) * 2 * w1 + 2 * w2;
        return 0;
    }
    cout << (n - k) * 2 * w1 + k * w2;
    return 0;
}