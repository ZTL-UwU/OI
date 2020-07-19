#include <iostream>
using namespace std;
const int MAXN = 2e7 + 10;
int p[MAXN];
inline string init(string str)
{
    string n_str;
    n_str = "$" + str + str + "#\0";
    for (int i = 1; i < n_str.size(); i++)
        n_str[i] = i % 2 ? '#' : str[i / 2 - 1];
    return n_str;
}
inline int Manacher(string str)
{
    int id = 0;
    int mx = 0;
    int maxn = -0x7fffffff;
    for (int i = 1; i < str.size(); i++)
    {
        if (i < mx)
            p[i] = min(p[id * 2 - i], mx - i);
        while (str[i - p[i]] == str[i + p[i]])
            p[i]++;
        if (i + p[i] > mx)
        {
            id = i;
            mx = i + p[i];
        }
        maxn = max(maxn, p[i] - 1);
    }
    return maxn;
}
int main()
{
    string str;
    cin >> str;
    str = init(str);
    cout << Manacher(str) << "\n";
    return 0;
}