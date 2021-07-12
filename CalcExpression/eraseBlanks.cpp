#include "eraseBlanks.hpp"

const char BLANK = ' ';

std::string eraseBlanks(const std::string &input)
{
	std::string result;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != BLANK)
		{
			result += input[i];
		}
	}
	return result;
}