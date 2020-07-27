#include <iostream>
using namespace std;
const int MAXN = 2e6; 
int p[MAXN];  
inline string init_str(string str)
{
    string n_str;
    n_str = "$" + str + str + "#\0";
    for (int i = 1; i < n_str.size(); i++)
        n_str[i] = i % 2 ? '#' : str[i / 2 - 1];
    return n_str;
}
inline int manacher(string str)
{
    int id = 0, mx = 0;
    int maxn = -0x7fffffff;
    for (int i = 1; i < str.size(); i++)
    {
        if (i < mx)
            p[i] = min(p[id * 2 - 1], mx - i);
        while (str[i - p[i]] == str[i + p[i]])
            p[i]++;
        if (i + p[i] > mx)
        {
            id = i;
            mx = i + p[i];
        }
        if (i % 2)
            for (int j = i; j >= max(max(i - p[i], j - (i - j)), 3); j-= 2)
                if (p[j] >= i - j && p[j - (i - j)] >= i - j)
                    maxn = max(maxn, 4 * (i - j));
    }
    return maxn;
}
int main()
{
    int n;
    string str;
    cin >> n >> str;
    str = init_str(str);
    cout << manacher(str) / 2;
    puts("");
    return 0;
}