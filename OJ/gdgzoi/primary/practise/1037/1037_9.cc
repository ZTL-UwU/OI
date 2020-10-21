#include <iostream>
using namespace std;
int main()
{
    int l;
    int m;
    cin >> l >> m;
    bool a[100000];
    for (int i = 0; i < 100000; i++)
        a[i] = true;
    int left, right;
    for (int i = 0; i < m; i++)
    {
        cin >> left >> right;
        for (int j = left; j <= right; j++)
            a[j] = false;
    }
    int c = 0;
    for (int i = 0; i <= l; i++)
        if (a[i] == true)
            c++;
    cout << c;
    return 0;
}