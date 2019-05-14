#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


void min(const std::string& str)
{
	char prev = '0';

	char curr = '0';

	size_t i = 0;

	for (; i < str.length(); ++i)
	{
		prev = curr;

		curr = str[i];

		if (i > 1)
		{
			if (prev < curr)
			{
				std::cout << str.find(prev) + 1 << std::endl;

				return;
			}
		}
	}

	std::cout << str.find(str[i - 1]) + 1 << std::endl;
}

int main()
{
	std::string str;

	std::getline(std::cin, str);

	std::getline(std::cin, str);
	
	min(str);

	return 0;
}