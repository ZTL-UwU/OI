#include <algorithm>
#include <iostream>
#include <utility>

const int MAX_N = 5e5 + 10;

std::pair<int, int> sum[MAX_N];
std::pair<int, int> sum_rev[MAX_N];

int pos[MAX_N];
int val[MAX_N];
int n, k, l, r;

class hp
{
private:
    void swap(int x, int y)
    {
        std::swap(base[x], base[y]);
        std::swap(rev[x], rev[y]);
    }

public:
    std::pair<int, bool> base[MAX_N];
    int rev[MAX_N];

    void roll_down()
    {
        int u = 1;
        while (u * 2 <= n)
        {
            int v = u * 2;

            if (v + 1 <= n && base[v].first < base[v + 1].first)
                v++;
            if (base[v].first > base[u].first)
            {
                swap(u, v);
                u = v;
            }
            else
                break;
        }
    }
};

bool check(int a, int b) { return sum[a].second - sum_rev[b].second >= l && sum[a].second - sum_rev[b].second <= r; }

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> k >> l >> r;

    sum[1] = {0, 1};
    sum_rev[1] = {0, 1};
    for (int i = 2; i <= n + 1; i++)
    {
        std::cin >> val[i];
        sum[i].first = sum[i - 1].first + val[i];
        sum[i].second = i;
        sum_rev[i].first = -sum[i].first;
        sum_rev[i].second = i;
    }
    std::sort(sum + 1, sum + n + 2,
              [](std::pair<int, int> p1, std::pair<int, int> p2) -> bool { return p1.first > p2.first; });
    std::sort(sum_rev + 1, sum_rev + n + 2,
              [](std::pair<int, int> p1, std::pair<int, int> p2) -> bool { return p1.first > p2.first; });

    n++;

    // for (int i = 1; i <= n; i++)
    //     std::cout << sum[i].first << " " << sum[i].second << "\n";
    // std::cout << "----\n";
    // for (int i = 1; i <= n; i++)
    //     std::cout << sum_rev[i].first << " " << sum_rev[i].second << "\n";

    hp heap;
    for (int i = 1; i <= n; i++)
    {
        heap.base[i].first = sum[i].first + sum_rev[1].first;
        heap.base[i].second = check(i, 1);

        // std::cout << heap.base[i].first << " " << heap.base[i].second << "\n";

        heap.rev[i] = i;
        pos[i] = 1;
    }

    long long int ans = 0;
    int kk = 0;
    int kkk = 0;
    while (kk < k && kkk < n * n)
    {
        if (heap.base[1].second)
        {
            ans += heap.base[1].first;
            kk++;
        }

        int index = heap.rev[1];
        pos[index]++;
        heap.base[1].first = sum[index].first + sum_rev[pos[index]].first;
        heap.base[1].second = check(index, pos[index]);

        heap.roll_down();
        kkk++;
    }

    std::cout << ans;
    return 0;
}
