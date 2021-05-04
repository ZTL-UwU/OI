#include <unordered_map>
#include <algorithm>
#include <iostream>

const int MAX_N = 3e4 + 10;

std::unordered_map<std::string, std::size_t> map1;
std::unordered_map<std::string, std::size_t> map2;
std::string answers[MAX_N];
int n, m, p, q;

std::string flip(std::string str)
{
    for (std::size_t i = 0; i < str.size(); i++)
        str[i] = str[i] == 'Y' ? 'N' : 'Y';
    return str;
}

bool flag = false;
void dfs(int step, std::string str)
{
    if (step == m)
    {
        if (map1[str] == p && map2[str] == q)
        {
            std::cout << str;
            flag = true;
        }
        return;
    }

    dfs(step + 1, str + "N");
    if (flag)
        return;
    dfs(step + 1, str + "Y");
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> p >> q;

    for (int i = 0; i < n; i++)
    {
        std::cin >> answers[i];
        map1[answers[i]]++;
        map2[flip(answers[i])]++;
    }
    std::sort(answers, answers + n);

    if (p == 0 && q == 0)
    {
        dfs(0, "");
        if (flag)
            return 0;
    }
    else if (p == 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (map1[answers[i]] == q)
            {
                std::cout << flip(answers[i]);
                return 0;
            }
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (map1[answers[i]] == p && map2[answers[i]] == q)
            {
                std::cout << answers[i];
                return 0;
            }
        }
    }

    std::cout << "-1";
    return 0;
}