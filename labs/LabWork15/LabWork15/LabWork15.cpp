#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using VecOfNums = std::vector<int>;

VecOfNums readVecOfNums(std::istream& stream)
{
	std::string str, str2;

	std::getline(stream, str);

	int num = 0;

	stream >> num;

	VecOfNums vec;

	for (int i = 0; i < num; ++i)
	{
		int n = 0;

		stream >> n;

		vec.push_back(n);
	}

	return vec;
}

bool isProgression(VecOfNums& vec)
{
	std::sort(vec.begin(), vec.end());

	for (size_t i = 1; i < vec.size() - 1; ++i)
	{
		if (vec[i] - vec[i - 1] != vec[i + 1] - vec[i])
		{
			return false;
		}
	}

	return true;
}

int main()
{
	int quantityOfTests = 0;

	std::cin >> quantityOfTests;

	for (int i = 0; i < quantityOfTests; ++i)
	{
		auto nums = readVecOfNums(std::cin);

		if (isProgression(nums))
		{
			std::cout << "Yes" << std::endl;
		}
		else
		{
			std::cout << "No" << std::endl;
		}
	}


	return 0;
}