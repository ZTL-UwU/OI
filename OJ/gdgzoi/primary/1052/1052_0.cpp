#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 1000;
int tmp[MAXN];
int a[MAXN];
int b[MAXN];
int n;
int get_len()
{
    int x = -1;
    for (int i = 0; i < n; i++)
        x = max(x, a[i]);
    int res = 0;
    while (x)
    {
        res++;
        x /= 10;
    }
    return res;
}
void cout_sort()
{
    int len = get_len();
    int key = 1;
    for (int k = 0; k < len; k++)
    {
        memset(b, 0, sizeof(b));
        for (int i = 0; i < n; i++) b[(a[i] / key) % 10]++;
        for (int i = 1; i < 10; i++) b[i] += b[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            tmp[b[(a[i] / key) % 10] - 1] = a[i];
            b[(a[i] / key) % 10]--;
        }
        for (int i = 0; i < n; i++)
            a[i] = tmp[i];
        key *= 10;
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout_sort();
    for (int i = n - 1; i >= 0; i--)
        cout << a[i] << " ";
    cout << "\n";
    return 0;
}