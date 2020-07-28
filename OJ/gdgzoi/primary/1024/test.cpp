#include <iostream>
using namespace std;
void flip(string &a)
{
    for (int i = 0; i < a.size() / 2; i++)
        swap(a[i], a[a.size() - i - 1]);
}
string add(string a, string b)
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
        c[i] = bit % 10 + '0';
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
inline string diff(string a, string b)
{
    if (bigger(b, a))
        swap(a, b);
    string c = a;
    while (a.size() > b.size())
        b = "0" + b;
    flip(a);
    flip(b);
    int x = 0;
    for (int i = 0; i < a.size(); i++)
    {
        int bit = a[i] - b[i] - x;
        a[i] += (bit < 0 ? 10 : 0);
        c[i] = a[i] - b[i] - x + '0';
        x = (bit < 0 ? 1 : 0);
    }
    int k = 0;
    while (c[c.size() - k - 1] == '0')
        k++;
    c = c.substr(0, c.size() - k);
    flip(c);
    return c;
}
int main()
{
    string a, b;
    cin >> a >> b;
    cout << bigger(a, b) << '\n';
    return 0;
}