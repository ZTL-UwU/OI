#include <iostream>
#include <stack>

int main()
{
    std::stack<char> st;
    std::stack<char> st_tmp;
    std::string str;

    std::cin >> str;
    for (auto c : str)
    {
        if (!st.empty() && c == st.top())
            st.pop();
        else
            st.push(c);
    }

    while (!st.empty())
    {
        st_tmp.push(st.top());
        st.pop();
    }

    while (!st_tmp.empty())
    {
        std::cout << st_tmp.top();
        st_tmp.pop();
    }
    return 0;
}
