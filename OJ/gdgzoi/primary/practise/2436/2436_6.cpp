#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <dbg.h>
using namespace std;
void add_zero(vector<int> &a, vector<int> &b)
{
    for (int i = min(a.size(), b.size()); i < max(a.size(), b.size()); i++)
        a.size() < b.size() ? a.push_back(0) : b.push_back(0);
}
void swap_v(vector<int> &x)
{
    for (int i = 0; i<x.size()>> 1; i++)
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
    add_zero(a, b);
    for (int i = 0; i < a.size(); i++)
        c.push_back((a[i] + b[i] + x) % 10000), x = (a[i] + b[i] + x) / 10000;
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
    add_zero(a, b);
    for (int i = 0; i < a.size(); i++)
    {
        int tmp = a[i] - b[i] - x;
        x = 0;
        if (tmp < 0)
            x = 1, tmp += 10000;
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
        int tmp = a[i] + x * 10000;
        b.push_back(tmp >> 1);
        x = 0;
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
    int times = 0;
    while (1)
    {
        times ++;
        if (a == b)
        {
            for (int i = 0; i < two1; i++)
                a = times_two(a);
            return a;
        }
        if (cmp(a, b))
        {
            vector<int> tmp = a, a = b, b = tmp;
            dbg("HI");
        }
        a = minuss(a, b);
        dbg(a);
        while (!(a[a.size() - 1] % 2))
            a = divide_by_two(a);
        dbg(a);
        if (times == 30) system("pkill 2436_6");
    }
}
int main()
{
    string s1, s2;
    vector<int> a, b;
    cin >> s1 >> s2;
    int add1, add2;
    int size1 = s1.size(), size2 = s2.size();
    for (add1 = 0; add1 < 4; add1++)
    {
        if ((size1 + add1) % 4 == 0)
            break;
        else
            s1 = "0" + s1;
    }
    for (add2 = 0; add2 < 4; add2++)
    {
        if ((size2 + add2) % 4 == 0)
            break;
        else
            s2 = "0" + s2;
    }
    for (int i = 0; i < s1.size(); i += 4)
    {
        int temp = 0;
        int k = 1;
        string tmp = s1.substr(i, 4);
        for (int i = tmp.size() - 1; i >= 0; i--)
            temp += (tmp[i] - '0') * k, k *= 10;
        a.push_back(temp);
    }
    for (int i = 0; i < s2.size(); i += 4)
    {
        int temp = 0;
        int k = 1;
        string tmp = s2.substr(i, 4);
        for (int i = tmp.size() - 1; i >= 0; i--)
            temp += (tmp[i] - '0') * k, k *= 10;
        b.push_back(temp);
    }
    vector<int> res = gcd(a, b);
    cout << res[0];
    for (int i = 1; i < res.size(); i++)
        cout << setfill('0') << setw(4) << res[i];
    cout << "\n";
    return 0;
}
