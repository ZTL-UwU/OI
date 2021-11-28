#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <map>

std::map<std::string, int> server;
int id = 0;

bool check_ip(std::string ip)
{
	std::vector<int> section;

	int last = 0;
	int d_cnt = 0;
	int dd_cnt = 0;
	for (std::size_t i = 0; i < ip.size(); i++)
	{
		if (ip[i] == ':' || ip[i] == '.' || i == ip.size() - 1)
		{
			if (ip[i] == ':')
				dd_cnt++;
			if (ip[i] == '.')
				d_cnt++;

			if (i == ip.size() - 1)
				i++;
			const std::string str = ip.substr(last, i - last);
			last = i + 1;

			std::stringstream ss;
			ss << str;
			int num;
			ss >> num;

			if (str.size() == 0 || (section.size() != 3 && ip[i] == ':') || std::to_string(num) != str)
			{
				std::cout << "ERR\n";
				return false;
			}

			section.push_back(num);
		}
	}

	if (section.size() != 5 || section[4] < 0 || section[4] > 65535 || dd_cnt != 1 || d_cnt != 3)
	{
		std::cout << "ERR\n";
		return false;
	}

	for (std::size_t i = 0; i < 4; i++)
	{
		if (section[i] < 0 || section[i] > 255)
		{
			std::cout << "ERR\n";
			return false;
		}
	}

	return true;
}

int main()
{
	std::freopen("network.in", "r", stdin);
	std::freopen("network.out", "w", stdout);

	int n;
	std::cin >> n;

	for (int i = 1; i <= n; i++)
	{
		std::string dev, ip;
		std::cin >> dev >> ip;

		if (check_ip(ip))
		{
			if (dev == "Server")
			{
				if (!server[ip])
				{
					server[ip] = i;
					std::cout << "OK\n";
				}
				else
					std::cout << "FAIL\n";
			}
			else
			{
				if (server[ip])
					std::cout << server[ip] << "\n";
				else
					std::cout << "FAIL\n";
			}
		}
	}

	return 0;
}