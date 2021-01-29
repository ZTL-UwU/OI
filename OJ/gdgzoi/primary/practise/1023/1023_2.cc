#include <iostream>
using namespace std;
long long a[200000];
long long n, c;
long long ans;
int main()
{
    cin >> n >> c;
    for (long long i = 0; i < n; i++)
        cin >> a[i];
    for (long long i = 0; i < n; i++)
    {
        long long l = i;
        long long r = n;
        while (r - l >= 0)
        {
            int mid = (l + r) / 2;
            if (a[mid] - a[i] == c)
            {
                ans++;
                int tmp = mid - 1;
                while (a[tmp] - a[i] == c && tmp >= 0)
                {
                    tmp--;
                    ans++;
                }
                tmp = mid + 1;
                while (a[tmp] - a[i] == c && tmp < n)
                {
                    tmp++;
                    ans++;
                }
                break;
            }
            else if (a[mid] - a[i] > c)
                r = mid - 1;
            else
                l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}