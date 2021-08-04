#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int y, z;
    std::cin >> y >> z;

    int ans = 0;
    for (int i = 1; i < 1e4; i++)
    {
        int new_z = z * i;

        bool flag = true;
        int sum = 0;
        while (new_z)
        {
            const int tmp = new_z % 10;
            sum += tmp;
            if (tmp == 0 || sum > y)
            {
                flag = false;
                break;
            }

            new_z /= 10;
        }

        if (sum != y)
            flag = false;
        if (flag)
            ans++;
    }

    std::cout << ans;
    return 0;
}
