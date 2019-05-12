#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

// Ильин Максим, ПС-21

//7.2.Скобки(4)
//Последовательность круглых скобок называют правильной, если можно добавить в
//нее числа и знаки арифметических операций так, что полученное алгебраическое
//выражение станет корректным.Например, скобочная последовательность(())()
//является правильной, а(())) и())(() такими не являются.Пустая последовательность
//	также считается правильной.
//	Задана правильная скобочная последовательность.Назовем парой внешних скобок
//	первую открывающую и последнюю закрывающую скобки.
//	После удаления пары внешних скобок правильность последовательности может как
//	сохраниться, так и нарушиться.Найти наибольшее число пар внешних скобок, которые
//	можно удалять до первого нарушения правильности последовательности.


bool IsValidExpression(const std::string& expression)
{
	int counter = 0;

	for (const auto& ch : expression)
	{
		if (ch == '(')
		{
			counter++;
		}

		if (ch == ')')
		{
			counter--;
		}

		if (counter < 0)
		{
			return false;
		}
	}

	return counter == 0;
}

int CountBracketsToRemove(const std::string& expression)
{
	int counter = 0;

	size_t rightBracketsCounter = 0;
	
	size_t leftBracketsCounter = 0;

	bool rightBracketHasBeenMet = false;

	for (const auto ch : expression)
	{
		if (ch == '(')
		{
			counter++;

			if (!rightBracketHasBeenMet)
			{
				leftBracketsCounter++;
			}

			rightBracketsCounter = 0;
		}

		if (ch == ')')
		{
			counter--;

			rightBracketsCounter++;
		
			rightBracketHasBeenMet = true;
		}

		if (counter < 0)
		{
			return -1;
		}
	}

	if (counter == 0)
	{
		return  std::min(rightBracketsCounter, leftBracketsCounter);
	}

	return -1;
}

void RemoveBraces(int quantity, std::string& str)
{
	str.erase(0, quantity);

	str.erase(str.length() - quantity, quantity);
}

int addMissingBrackets(std::string& str, int removeBracketsQuantity)
{
	int addedBracketsQ = 0;

	while (!IsValidExpression(str))
	{
		str.insert(str.begin(), '(');
		
		str.push_back(')');
	
		addedBracketsQ++;

		if (addedBracketsQ == removeBracketsQuantity + 1)
		{
			return -1;
		}
	}

	return addedBracketsQ;
}

int HowManyBracketsCouldBeRemoved(std::string expression)
{
	const auto bracketsForRemove = CountBracketsToRemove(expression);

	if (bracketsForRemove == -1)
	{
		return 0;
	}

	RemoveBraces(bracketsForRemove, expression);

	const auto addedBracketsQ = addMissingBrackets(expression, bracketsForRemove);

	if (addedBracketsQ == -1)
	{
		return 0;
	}

	return bracketsForRemove - addedBracketsQ;
}

int main()
{
	std::ifstream in("input.txt");

	std::ofstream out("output.txt");

	std::string str;

	std::getline(in, str);

	std::getline(in, str);

	out << HowManyBracketsCouldBeRemoved(str) << std::endl;

	return 0;
}