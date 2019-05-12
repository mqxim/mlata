#include <string>
#include <fstream>

// 13.6.Строка(4)

// В заданной строке символов из заглавных латинских букв найти подстроку, которая включает
// наибольшее количество букв, встречающихся в этой подстроке в единственном экземпляре.Если
// таких строк несколько, выдать наименьшую по алфавиту.

void UpdateMaxSubstr(std::string& maxSubstr, std::string& currentSubstr)
{
	if (currentSubstr.length() == maxSubstr.length())
	{
		maxSubstr = maxSubstr.compare(currentSubstr) <= 0 ? maxSubstr : currentSubstr;
	}
	else if (currentSubstr.length() > maxSubstr.length())
	{
		maxSubstr = currentSubstr;
	}
}

std::string GetMaxSubstrWithoutRepeatingChars(const std::string& str)
{
	std::string maxSubstr;

	std::string currentSubstr;

	for (const auto& ch : str)
	{
		const auto extraCharPos = currentSubstr.find(ch);

		if (extraCharPos != std::string::npos)
		{
			UpdateMaxSubstr(maxSubstr, currentSubstr);

			currentSubstr = currentSubstr.substr(extraCharPos + 1);
		}

		currentSubstr += ch;
	}

	UpdateMaxSubstr(maxSubstr, currentSubstr);

	return maxSubstr;
}

int main()
{
	std::ifstream input("input.txt");

	std::ofstream output("output.txt");

	std::string str;

	std::getline(input, str);

	std::getline(input, str);

	output << GetMaxSubstrWithoutRepeatingChars(str) << std::endl;

	return 0;
}