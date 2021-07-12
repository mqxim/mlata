#include "stringOperations.hpp"

using namespace std;

template<typename type> char digitToString(type number)
{
	char result = ((number < 1) ? '0' :
		(number < 2) ? '1' :
		(number < 3) ? '2' :
		(number < 4) ? '3' :
		(number < 5) ? '4' :
		(number < 6) ? '5' :
		(number < 7) ? '6' :
		(number < 8) ? '7' :
		(number < 9) ? '8' :
		(number < 10) ? '9' : '?');

	return result;
}

string reverseString(string str)
{
	char ch;
	size_t index;
	size_t strlength = str.length();
	for (size_t i = 0; i < strlength / 2; i++)
	{
		ch = str[i];
		index = strlength - i - 1;
		str[i] = str[index];
		str[index] = ch;
	}
	return str;
}

string intToString(int number)
{
	string result = "";
    string sign = "";
	int digit;
	if (number == 0)
	{
		return "0";
	}
    if (number < 0)
    {
		number = number * -1;
       	sign = "-";
    }
	while (number)
	{
		digit = number % 10;
		number = number / 10;
		result = result + digitToString(digit);
	}
	return sign + reverseString(result);
}