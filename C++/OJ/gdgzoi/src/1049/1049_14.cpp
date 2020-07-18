#include <iostream>
using namespace std;
const int MAXN = 1e5;
int nextt[MAXN];
int k;
void get_nextt(string s)
{
    int j = -1;
    for (int i = 0; i < s.size(); i++)
    {
        while (j < 0 || s[i] != s[j])
    }
}
int main()
{
    string s;
    cin >> s;
    cin >> k;
    for (int i = 0; i < s.size(); i++)
        get_nextt(s.substr(i, s.size() - i));
    return 0;
}