#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
const int MAXN = 100010;
int v[MAXN];
bool is_prime[MAXN];
vector<int> prime;
void init_prime(int size)
{
    for (int i = 0; i < MAXN; i++)
        is_prime[i] = 1;
    for (int i = 2; i <= size; i++)
    {
        if (is_prime[i])
        {
            int col = 1;
            prime.push_back(i);
            v[i - 1] = col;
            for (int j = i * 2; j <= size; j++)
                is_prime[j] = false, v[j - 1] = !(j & 1) + 1;
        }
    }
}
int main()
{
    int n;
    init_prime(100001);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
    return 0;
}