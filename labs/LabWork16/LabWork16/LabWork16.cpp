#include <iostream>

using namespace std;


bool isValidExpression(string const& str, const size_t startPos)
{
	int counter = 0;

	for (size_t i = startPos; i < str.length(); ++i)
	{
		if (str[i] == '(')
			counter++;

		if (str[i] == ')')
			counter--;

		if (counter < 0)
			return false;
	}

	for (size_t i = 0; i < startPos; ++i)
	{
		if (str[i] == '(')
			counter++;

		if (str[i] == ')')
			counter--;

		if (counter < 0)
			return false;
		
	}

	return counter == 0;
}

bool hasEnoughBrackets(const string& str)
{
	int l = 0;	int r = 0;
	
	for (const auto ch : str)
	{
		if (ch == '(')
			l++;

		if (ch == ')')
			r++;
	}

	return r == l;
}

size_t getPos(string& str)
{	
	size_t startPos = 0;

	while (!isValidExpression(str, startPos))
	{
		startPos++;
	}

	return startPos;
}

int main()
{
	int n;
	string str;
	cin >> n >> str;
	
	if (!hasEnoughBrackets(str))
	{
		cout << "No\n";
		return 0;
	}

	cout << 1 + getPos(str) << endl;

	return 0;
}