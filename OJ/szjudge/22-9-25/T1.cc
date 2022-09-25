#include <unordered_map>
#include <iostream>

std::unordered_map<std::string, bool> mp;

int main()
{
	std::string a, b;
	std::cin >> a >> b;
	
	int ans = 0;
	for (int i = 0; i <= a.size(); i++)
	{
		for (int j = 0; j <= b.size(); j++)
		{
			auto aa = a.substr(0, i);
			auto bb = b.substr(j, b.size() - j);
			if (!mp[aa + bb])
			{
				mp[aa + bb] = true;	
				ans++;
			}
		}
	}
	
	std::cout << ans;
	return 0;
}