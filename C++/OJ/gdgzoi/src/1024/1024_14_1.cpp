#include <iostream>
using namespace std;
const int MAXN = 6e3;
long long price[MAXN];
long long days[MAXN];
string ways[MAXN];
inline void flip(string &a)
{
    for (int i = 0; i < a.size() / 2; i++)
        swap(a[i], a[a.size() - i - 1]);
}
inline string add(string a, string b)
{
    if (b.size() > a.size())
        swap(a, b);
    string c = a;
    while (a.size() - b.size())
        b = "0" + b;
    flip(a);
    flip(b);
    int x = 0;
    for (int i = 0; i < a.size(); i++)
    {
        int bit = a[i] - '0' + b[i] - '0' + x;
        c[i] = (bit % 10) + '0';
        x = bit / 10;
    }
    if (x)
        c += (x + '0');
    flip(c);
    return c;
}
inline bool bigger(string a, string b)
{
    if (a.size() != b.size())
        return a.size() > b.size();
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return a[i] > b[i];
    return false;
}
inline string maxx(string a, string b)
{
    return bigger(a, b) ? a : b;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> price[i];
    n++;
    for (int i = 0; i < n; i++)
    { 
        days[i] = 1;
        for (int j = 0; j < i; j++)
            if (price[j] > price[i])
                days[i] = max(days[i], days[j] + 1);
        long long last = price[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (price[j] > price[i] && days[j] + 1 == days[i] && price[j] != last)
            {
                ways[i] = add(ways[i], ways[j]);
                last = price[j];
            }
        }
        if (bigger("1", ways[i]))
            ways[i] = "1";
    }
    cout << days[n - 1] - 1 << " " << ways[n - 1] << "\n";
    return 0;
}