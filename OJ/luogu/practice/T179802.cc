#include <iostream>
#include <stack>
#include <array>

const int MAX_N = 1e6 + 10;

int before[MAX_N];
int after[MAX_N];
int a[MAX_N];
int n;

void solve(bool from_first)
{
    std::stack<int> st;

    for (int i = from_first ? 0 : n - 1; from_first ? i < n : i >= 0; from_first ? i++ : i--)
    {
        while (!st.empty() && a[st.top()] < a[i])
            st.pop();

        if (!st.empty())
        {
            if (from_first)
                before[i] = st.top() + 1;
            else
                after[i] = st.top() + 1;
        }

        st.push(i);
    }
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        before[i] = -1;
        after[i] = -1;
    }

    solve(true);
    solve(false);

    for (int i = 0; i < n; i++)
        std::cout << before[i] << " " << after[i] << "\n";
    return 0;
}
