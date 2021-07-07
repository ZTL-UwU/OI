#include <iostream>

const int TABLE[6] = {1, 5, 10, 50, 100, 500};
int num[6];
int n;

int main()
{
    for (int i = 0; i < 6; i++)
        std::cin >> num[i];
    std::cin >> n;

    int ans = 0;
    int last = 5;
    while (n != 0)
    {
        if (num[last] && n >= TABLE[last])
        {
            num[last]--;
            n -= TABLE[last];
            ans++;
        }
        else
            last--;
    }

    std::cout << ans;
    return 0;
}