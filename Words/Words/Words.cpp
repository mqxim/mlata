#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>

//  Ильин Максим, ПС-21

//  8.1.Слова(3)
//  Дано слово, состоящее из M(2 ≤ M ≤ 7) строчных букв латинского алфавита.Найти все
//  перестановки символов данного слова.

bool CreatePermutation(std::string& str)
{
	if (str.length() <= 1)
	{
		return false;
	}

	auto leftSymbolIterator = --str.end();

	for (;;)
	{
		auto rightSymbolIterator = leftSymbolIterator--;

		if (*leftSymbolIterator < *rightSymbolIterator)
		{
			auto minForSwapIterator = str.end();
		
			do
			{
				minForSwapIterator -= 1;
			}
			while (*leftSymbolIterator >= *minForSwapIterator);

			std::swap(*leftSymbolIterator, *minForSwapIterator);

			std::reverse(rightSymbolIterator, str.end());
			
			return true;
		}
		
		if (leftSymbolIterator == str.begin())
		{
			return false;
		}
	}
}

int main()
{
	std::ifstream in("input.txt");

	std::ofstream out("output.txt");

	std::string str;

	std::getline(in, str);

	std::sort(str.begin(), str.end());
	
	out << str << std::endl;

	while (CreatePermutation(str))
	{
		out << str << std::endl;
	}

	return 0;
}