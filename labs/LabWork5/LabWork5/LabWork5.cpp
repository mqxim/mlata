#include "pch.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

std::ifstream input;

using Number = unsigned long long;

void initVec(std::vector<Number>& vec)
{
	std::string inStr;

	std::getline(std::cin, inStr);

	std::istringstream strStream(inStr);

	Number num;

	while (strStream >> num)
	{
		vec.push_back(num);
	}

	std::sort(vec.begin(), vec.end(), [](Number first, Number second) {
		return first < second;
	});
}

int main()
{
	std::string inStr; std::getline(std::cin, inStr);

	std::vector<Number> sellers, buyers;

	initVec(sellers); initVec(buyers);

	Number maxPrice = 0; Number sum = 0;

	size_t g = 0;

	for (size_t i = 0; i < buyers.size(); i++)
	{
		for (g; g < sellers.size(); g++)
		{
			if (sellers[g] > buyers[i])
			{
				Number q = (buyers.size() - i > g) ? g : (buyers.size() - i);
				Number checkSum = buyers[i] * q;
				
				if (checkSum > sum)
				{
					sum = checkSum;
					maxPrice = buyers[i];
				}

				break;
			}
		}
	}

	std::cout << maxPrice << " " << sum << std::endl;

	return 0;
}