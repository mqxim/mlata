#include <iostream>
#include <string>
#include <fstream>

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

	return  counter == 0;
}

bool RemoveExtremePairOfBrackets(std::string& expression)
{
	if (expression.length() < 2)
	{
		return false;
	}

	expression.erase(expression.begin());

	expression.erase(expression.end() - 1);

	return true;
}

int HowManyBracketsCouldBeRemoved(std::string expression)
{
	int counter = 0;

	while (RemoveExtremePairOfBrackets(expression) && IsValidExpression(expression))
	{
		counter++;
	}

	return counter;
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