#include <iostream>

const int MAX_N = 1e5 + 10;

int max_mid[MAX_N];
int ra[2 * MAX_N];
int l[2 * MAX_N];
int r[2 * MAX_N];

std::string init_str(std::string str)
{
    std::string n_str = "%$" + str + str + "#";

    for (int i = 1; i < n_str.size(); i++)
        n_str[i] = i % 2 ? '#' : str[i / 2 - 1];
    return n_str;
}

void manacher(std::string str)
{
    str = init_str(str);
    int mx = 0;
    int id = 0;
    for (int i = 1; i <= str.size(); i++)
    {
        if (i < mx)
            ra[i] = std::min(ra[2 * id - i], mx - i);
        else ra[i] = 1;

        while (str[i - ra[i]] == str[i + ra[i]])
            ra[i]++;

        if (mx < i + ra[i])
        {
            mx = i + ra[i];
            id = i;
        }

        l[i + ra[i] - 1] = std::max(l[i + ra[i] - 1], ra[i] - 1);
        r[i - ra[i] + 1] = std::max(r[i - ra[i] + 1], ra[i] - 1);
    }
}

int main()
{
    std::string str;
    std::cin >> str;

    manacher(str);
    for (int i = 3; i < str.size(); i += 2)
        r[i] = std::max(r[i], r[i - 2] - 2);
    for (int i = str.size() - 1; i >= 3; i -= 2)
        l[i] = std::max(l[i], l[i - 2] - 2);

    int ans = 0;
    for (int i = 3; i < str.size(); i += 2)
        if (l[i] && r[i])
            ans = std::max(ans, l[i] + r[i]);
    std::cout << ans;
    return 0;
}