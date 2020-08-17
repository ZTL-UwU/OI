#include <iostream>
using namespace std;
const int MAXN = 1e5 + 10;
int h[MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> h[i];
    int ans = 1;
    int con = 0;
    if (h[1] >= h[0]) con = 1;
    for (int i = 0; i < n; i++)
    {
        if (con == 0 && i == n - 1)
        {
            ans++;
            break;
        }
        if (con == 1 && h[i] > h[i + 1])
        {
            con = 0;
            ans++;
            continue;
        }
        if (con == 0 && h[i] < h[i + 1])
        {
            con = 1;
            ans++;
            continue;
        }
    }
    cout << ans;
    return 0;
}