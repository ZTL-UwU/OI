#include <iostream>
using namespace std;
int main()
{
    int ans = 0;
    for (int i = 1; i <= 50; i++)
    {
        int k = i * 2;
        ans += k * k * k;
    }
    cout << ans;
    return 0;
}