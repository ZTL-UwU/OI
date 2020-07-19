#include <iostream>
using namespace std;
int main()
{
    int ans = 0;
    int n;
    cin >> n;
    for (int i = 0; i < 26; i++)
    {
        int tmp;
        cin >> tmp;
        if (tmp)
            ans += tmp / n;
    }
    cout << ans << "\n";
    return 0;
}