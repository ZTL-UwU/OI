#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct machine
{
    long long int last_work_time;
    int time;
    inline long long int work();
    inline bool operator<(const machine x) const;
};

inline long long int machine::work()
{
    this->last_work_time += this->time;
    return this->last_work_time;
}

inline bool machine::operator<(const machine x) const
{
    return this->last_work_time + this->time > x.last_work_time + x.time;
}

std::priority_queue<machine> washing, drying;
std::vector<long long int> wash_time, dry_time;
int l, n, m;

inline void input(int num, std::priority_queue<machine> &m)
{
    for (int i = 0; i < num; i++)
    {
        int time;
        std::cin >> time;
        m.push((machine){0, time});
    }
}

inline void work(std::vector<long long int> &t, std::priority_queue<machine> &m)
{
    for (int i = 1; i <= l; i++)
    {
        machine x = m.top();
        m.pop();
        t.push_back(x.work());
        m.push(x);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> l >> n >> m;
    input(n, washing);
    input(m, drying);

    work(wash_time, washing);
    work(dry_time, drying);

    std::sort(wash_time.begin(), wash_time.end());
    std::sort(dry_time.begin(), dry_time.end(), std::greater<long long int>());

    long long int ans = -1;
    for (int i = 0; i < l; i++)
        ans = std::max(ans, wash_time[i] + dry_time[i]);

    std::cout << ans;
    return 0;
}