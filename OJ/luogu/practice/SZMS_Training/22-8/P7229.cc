#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

const int INF = 0x7fffffff;
using vc = std::vector<char>;
using ll = long long;

int p, m;

bool priority_cmp(char op1, char op2)
{
	if (op2 == '(')
		return true;
	else if (op2 == '*' && (op1 == '+' || op1 == '-' || op1 == '('))
		return true;
	else if ((op2 == '+' || op2 == '-') && op1 == '(')
		return true;
	else
		return false;
}

vc in2suf(std::string in)
{
	vc suf;
	std::stack<char> op;

	for (int i = 0; i < in.size(); i++)
	{
		const char c = in[i];

		if (('0' <= c && c <= '9') || c == 'x') { suf.push_back(c); }
		else
		{
			if (('0' <= in[i - 1] && in[i - 1] <= '9') || in[i - 1] == 'x')
				suf.push_back('#');
			if (c == ')')
			{
				while(op.top() != '(')
				{
					suf.push_back(op.top());
					op.pop();
				}
				op.pop();
			}
			else if (op.empty() || priority_cmp(op.top(), c)) { op.push(c); }
			else
			{
				while (!op.empty() && (!priority_cmp(op.top(), c)))
				{
					suf.push_back(op.top());
					op.pop();
				}
				op.push(c);
			}
		}
	}

	if (suf.back() != '#')
		suf.push_back('#');

	while (!op.empty())
	{
		suf.push_back(op.top());
		op.pop();
	}

	return suf;
}

ll calc_suf(vc suf, int x)
{
	std::stack<ll> num;
	ll val = 0;

	for (auto c : suf)
	{
		if ('0' <= c && c <= '9')
			val = (val * 10 + c - '0') % m;
		else if (c == 'x')
			val = x;
		else if (c == '#')
		{
			num.push(val % m);
			val = 0;
		}
		else
		{
			ll n1 = num.top();
			num.pop();
			ll n2 = num.top();
			num.pop();

			if (c == '+') { val = (n1 + n2) % m; }
			if (c == '-') { val = (n2 - n1 + m) % m; }
			if (c == '*') { val = (n1 * n2 % m) % m; }

			num.push(val);
			val = 0;
		}
	}

	return num.top();
}

int main()
{
	std::string exp;
    std::cin >> exp;
	std::cin >> p >> m;

	const auto res = in2suf(exp);

	// for (auto c : res)
	// 	std::cout << c;
	// std::cout << "\n";

	const ll b = calc_suf(res, 0);
	const ll k = calc_suf(res, 1) - b;

	for (int i = 1; i <= m; i++)
	{
		ll tmp = k * i + b;
		if ((tmp % m + m) % m == p)
		{
			std::cout << i;
			break;
		}
	}

	return 0;
}