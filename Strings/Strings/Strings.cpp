#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>

std::string GetMaxSubstrWithoutRepeatingChars(const std::string& str)
{
	std::string maxSubstr, currentSubstr;

	std::set<char> metChars;

	for (const auto& ch : str)
	{
		if (metChars.find(ch) == metChars.end())
		{
			currentSubstr += ch;

			metChars.insert(ch);
		}
		else
		{
			if (currentSubstr.length() == maxSubstr.length())
			{
				maxSubstr = maxSubstr.compare(currentSubstr) <= 0  ? maxSubstr : currentSubstr;
			}
			else if (currentSubstr.length() > maxSubstr.length())
			{
				maxSubstr = currentSubstr;
			}

			currentSubstr.erase(currentSubstr.begin());
		
			currentSubstr += ch;
		}
	}

	return  maxSubstr;
}

int main()
{
	std::ifstream input("input.txt");

	std::ofstream output("output.txt");

	std::string str;

	std::getline(std::cin, str);

	std::cout << GetMaxSubstrWithoutRepeatingChars(str) << std::endl;

	return 0;
}