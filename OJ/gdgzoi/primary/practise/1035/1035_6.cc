#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
struct _data
{
    int id, t, period;
    bool operator < (const _data x)const
    {
        return this->t > x.t || (this->t == x.t && this->id > x.id);
    }
};
priority_queue<_data> q;
int main()
{
    string tmp;
    while (1)
    {
        cin >> tmp;
        if (tmp == "#") break;
        int id, period;
        cin >> id >> period;
        q.push((_data){id, period, period});
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i ++)
    {
        _data tp = q.top();
        q.pop();
        cout << tp.id << endl;
        q.push((_data){tp.id, tp.t + tp.period, tp.period});
    }
    return 0;
}