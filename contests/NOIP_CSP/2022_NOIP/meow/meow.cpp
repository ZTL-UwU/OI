#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>

const int MAX_M = 1e6 + 10;
const int MAX_N = 1000;

struct card
{
    int num;
    int next;
};

struct op
{
    int name;
    int s1;
    int s2;
};

int last[MAX_N];
card a[MAX_M];
std::vector<op> ans;
std::deque<card> dq[MAX_N];

void init()
{
    for (int i = 0; i < MAX_N; i++)
    {
        last[i] = -1;
        dq[i].clear();
    }

    ans.clear();
}

int main()
{
    std::freopen("meow.in", "r", stdin);
    std::freopen("meow.out", "w", stdout);

    int T;
    std::cin >> T;

    for (int _i = 0; _i < T; _i++)
    {
        init();
        int n, m, k;
        std::cin >> n >> m >> k;

        for (int i = 0; i < m; i++)
        {
            std::cin >> a[i].num;
            if (last[a[i].num] != -1)
                a[last[a[i].num]].next = i;
            last[a[i].num] = i;
        }

        for (int i = 0; i < m; i++)
        {
            bool flag = false;
            for (int j = 0; j < n; j++)
            {
                if (!dq[j].empty() && dq[j].front().num == a[i].num)
                {
                    dq[j].pop_front();
                    flag = true;
                    ans.push_back((op){1, j, 0});
                    break;
                }
            }
            if (!flag)
            {
                for (int j = 0; j < n; j++)
                {
                    if (dq[j].empty() || dq[j].front().next > a[i].next)
                    {
                        flag = true;
                        dq[j].push_front(a[i]);
                        ans.push_back((op){1, j, 0});
                        break;
                    }
                }
            }

            for (int j = 0; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    if (!dq[j].empty() && !dq[k].empty() && dq[j].back().num == dq[k].back().num)
                    {
                        dq[j].pop_back();
                        dq[k].pop_back();
                        ans.push_back((op){2, j, k});
                        break;
                    }
                }
            }
        }

        std::cout << ans.size() << "\n";
        for (auto i : ans)
        {
            if (i.name == 1)
                std::cout << "1 " << i.s1 + 1 << "\n";
            else
                std::cout << "2 " << i.s1 + 1 << " " << i.s2 + 1 << "\n";
        }
    }
    return 0;
}
