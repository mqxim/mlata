#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

// Ильин Максим, ПС-21

//  6.2.Длинное деление(7)

//  Заданы два целых положительных числа.Требуется найти их частное и остаток от деления.
//  Ввод.В первой строке файла INPUT.TXT задано делимое, во второй – делитель.Количество
//  цифр делимого и делителя от 1 до 100.
//  Вывод.В первой строке файла OUTPUT.TXT вывести частное, во второй строке - остаток.

typedef std::vector<int> Number;

Number fromInt(unsigned x)
{
	Number result;
	
	while (x)
	{
		result.push_back(x % 10);
		x /= 10;
	}
	
	return result;
}

Number fromString(std::string const& str)
{
	Number result;
	
	for (int i = str.length() - 1; i >= 0; i--)
	{
		result.push_back(str[i] - '0');
	}
	
	return result;
}

std::string toString(Number const& num)
{
	if (num.size() == 0)
	{
		return "0";
	}

	std::string result;
	
	for (int i = num.size() - 1; i >= 0; i--)
	{
		result.push_back('0' + num[i]);
	}
	
	return result;
}

void normalize(Number& n)
{
	for (int i = 0; i < n.size(); i++)
	{
		if (n[i] < 0)
		{
			n[i] += 10;
			n[i + 1]--;
		}
	}

	for (int i = 0; i < n.size(); i++)
	{
		if (n[i] < 10)
		{
			continue;
		}

		if (i < n.size() - 1)
		{
			n[i + 1] += n[i] / 10;
		}
		else
		{
			n.push_back(n[i] / 10);
		}

		n[i] %= 10;
	}

	while (n.size() > 0 && n.back() == 0)
	{
		n.pop_back();
	}
}

Number operator+(Number a, Number const& b)
{
	if (a.size() < b.size())
	{
		a.resize(b.size());
	}

	for (int i = 0; i < b.size(); i++)
	{
		a[i] += b[i];
	}

	normalize(a);

	return a;
}

Number operator-(Number a, Number const& b)
{
	for (int i = 0; i < b.size(); i++)
	{
		a[i] -= b[i];
	}

	normalize(a);

	return a;
}

Number operator*(Number a, unsigned b)
{
	for (int i = 0; i < a.size(); i++)
	{
		a[i] *= b;
	}

	normalize(a);

	return a;
}

Number operator*(Number const& a, Number b)
{
	Number result;

	for (int i = 0; i < a.size(); i++)
	{
		result = result + b * a[i];
		b = b * 10;
	}

	return result;
}

bool operator>(Number const& a, Number const& b)
{
	if (a.size() > b.size())
	{
		return true;
	}

	if (b.size() > a.size())
	{
		return false;
	}

	for (int i = a.size() - 1; i >= 0; i--)
	{
		if (a[i] != b[i])
		{
			return a[i] > b[i];
		}
	}

	return false;
}

bool operator<(Number const& a, Number const& b)
{
	return b > a;
}

bool operator>=(Number const& a, Number const& b)
{
	return !(a < b);
}

bool operator<=(Number const& a, Number const& b)
{
	return !(a > b);
}

Number operator/(Number a, Number const& b)
{
	Number x = fromInt(1);

	while (x * b * 10 < a)
	{
		x = x * 10;
	}

	Number result;

	while (!x.empty())
	{
		int k = 0;

		while (a >= b * x * (k + 1))
		{
			k++;
		}

		result.push_back(k);

		a = a - b * x * k;

		x.erase(x.begin());
	}

	std::reverse(result.begin(), result.end());

	normalize(result);

	return result;
}

int main()
{
	std::ifstream in("input.txt");

	std::ofstream out("output.txt");

	int la, lb;

	std::string sa, sb;

	in >> la >> lb >> sa >> sb;

	Number a = fromString(sa);

	Number b = fromString(sb);

	Number d = a / b;

	Number q = a - b * d;

	out << toString(d) << std::endl << toString(q) << std::endl;

	return 0;
}