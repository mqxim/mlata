#include "pch.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <array>
#include <climits>

using namespace std;

const int MAX_ARR_SIZE = 100000;

using arr = std::array<int, MAX_ARR_SIZE>;

int getNumber()
{
	int number;
	cin >> number;
	return number;
}

void countMinQ()
{
	int num = getNumber();

	arr elems;
	
	for (int i = 0; i < MAX_ARR_SIZE; i++)
	{
		elems[i] = INT_MAX;
	}

	elems[0] = 0;

	for (int i = 1; i <= num; i++)
	{
		for (int j = 1; j*j <= i; j++) 
		{
			int previous = elems[i - int(std::pow(j, 2))] + 1;
			elems[i] = std::min(elems[i], previous);
		}
	}

	std::cout << num << " " << elems[num] << std::endl;

}

int main()
{
	countMinQ();
	return 0;
}