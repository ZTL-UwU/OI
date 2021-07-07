#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
void swap_v(vector<int> &x)
{
    for (int i = 0; i < x.size() / 2; i++)
        swap(x[i], x[x.size() - i - 1]);
}
bool cmp(vector<int> a, vector<int> b)
{
    if (a.size() != b.size())
        return a.size() < b.size() ? true : false;
    else
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return a[i] < b[i] ? true : false;
}
vector<int> add(vector<int> a, vector<int> b)
{
    swap_v(a);
    swap_v(b);
    vector<int> c;
    int x = 0;
    for (int i = min(a.size(), b.size()); i < max(a.size(), b.size()); i++)
        a.size() < b.size() ? a.push_back(0) : b.push_back(0);
    for (int i = 0; i < a.size(); i++)
        c.push_back((a[i] + b[i] + x) % 10), x = (a[i] + b[i] + x) / 10;
    if (x)
        c.push_back(1);
    swap_v(c);
    return c;
}
vector<int> minuss(vector<int> a, vector<int> b)
{
    swap_v(a);
    swap_v(b);
    vector<int> c;
    int x = 0;
    for (int i = min(a.size(), b.size()); i < max(a.size(), b.size()); i++)
        a.size() < b.size() ? a.push_back(0) : b.push_back(0);
    for (int i = 0; i < a.size(); i++)
    {
        int tmp = a[i] - b[i] - x;
        x = 0;
        if (tmp < 0)
            tmp += 10, x = 1;
        c.push_back(tmp);
    }
    while (!c[c.size() - 1])
        c.pop_back();
    swap_v(c);
    return c;
}
vector<int> times_two(vector<int> a)
{
    vector<int> b = add(a, a);
    return b;
}
vector<int> divide_by_two(vector<int> a)
{
    vector<int> b;
    int x = 0;
    for (int i = 0; i < a.size(); i++)
    {
        int tmp = a[i] + x * 10;
        x = 0;
        b.push_back(tmp / 2);
        if (tmp % 2)
            x = 1;
    }
    swap_v(b);
    while (!b[b.size() - 1])
        b.pop_back();
    swap_v(b);
    return b;
}
vector<int> gcd(vector<int> a, vector<int> b)
{
    int two1, two2;
    for (two1 = 0; !(a[a.size() - 1] % 2); two1++)
        a = divide_by_two(a);
    for (two2 = 0; !(b[b.size() - 1] % 2); two2++)
        b = divide_by_two(b);
    two1 = min(two1, two2);
    while (1)
    {
        if (a == b)
        {
            for (int i = 0; i < two1; i++)
                a = times_two(a);
            return a;
        }
        if (cmp(a, b))
        {
            vector<int> tmp = a;
            a = b;
            b = tmp;
        }
        a = minuss(a, b);
        while (!(a[a.size() - 1] % 2))
            a = divide_by_two(a);
    }
}
int main()
{
    string s1, s2;
    vector<int> a, b;
    cin >> s1 >> s2;
    for (int i = 0; i < s1.size(); i++)
        a.push_back(s1[i] - '0');
    for (int i = 0; i < s2.size(); i++)
        b.push_back(s2[i] - '0');
    vector<int> res = gcd(a, b);
    for (int i = 0; i < res.size(); i++)
        cout << res[i];
    cout << "\n";
    return 0;
}