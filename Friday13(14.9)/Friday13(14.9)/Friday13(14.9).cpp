#include <iostream>
#include <vector>
#include <fstream>

// Ильин Максим, ПС-21

//14.9.Пятница 13 (5)
//Перечислить дни, на которые приходится пятница 13 - го числа в заданном диапазоне лет из
//интервала 1901 - 2099 г.г.

const int INITIAL_YEAR = 1900;

const int END_YEAR = 2099;

const int INITIAL_DAY = 6;

int GetNumberOfWeekDayOfThirteenDayInJanuary(const int year)
{
	const auto yearsGone = (year - INITIAL_YEAR);

	const int quantityOfLeapYears = (yearsGone % 4 == 0) ? yearsGone / 4 - 1 : yearsGone / 4;

	return (yearsGone + INITIAL_DAY + quantityOfLeapYears) % 7;
}

bool IsLeapYear(int year)
{
	return !((year % 4 != 0) || ((year % 100 == 0) && (year % 400 != 0)));
}

std::vector<std::string> GetMonthsOfFridayThirteenAccordingToYear(int year)
{
	const auto day13InJanuary = GetNumberOfWeekDayOfThirteenDayInJanuary(year);

	if (IsLeapYear(year))
	{
		switch (day13InJanuary)
		{
		case 1:
			return { "MARCH", "NOVEMBER" };
		case 2:
			return { "FEBRUARY", "AUGUST" };
		case 3:
			return { "MAY" };
		case 4:
			return { "OCTOBER" };
		case 5:
			return { "JANUARY", "APRIL", "JULY" };
		case 6:
			return { "SEPTEMBER", "DECEMBER" };
		case 0:
			return { "JUNE" };
		}
	}
	else
	{
		switch (day13InJanuary)
		{
		case 1:
			return { "JUNE" };
		case 2:
			return { "FEBRUARY", "MARCH", "NOVEMBER" };
		case 3:
			return { "AUGUST" };
		case 4:
			return { "MAY" };
		case 5:
			return { "JANUARY", "OCTOBER" };
		case 6:
			return { "APRIL", "JULY" };
		case 0:
			return { "SEPTEMBER", "DECEMBER" };
		}
	}

	return  {};
}

int main()
{
	int startYear, endYear;

	std::ifstream in("input.txt");

	std::ofstream out("output.txt");

	while (in >> startYear >> endYear)
	{
		if (startYear < INITIAL_YEAR || startYear > END_YEAR || endYear < INITIAL_YEAR || endYear > END_YEAR)
		{
			out << "Year overflow" << std::endl;

			continue;
		}
	
		for (int i = startYear; i <= endYear; ++i)
		{
			auto vecOfMonths = GetMonthsOfFridayThirteenAccordingToYear(i);

			for (const auto& el : vecOfMonths)
			{
				out << i << " " << el << std::endl;
			}
		}
	}

	return 0;
}