#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<pair<int, int>> InitCoords()
{
	vector<pair<int, int>> coords;

	int quantityOfCoords;

	string inStr;
	
	getline(cin, inStr);

	while (getline(cin, inStr))
	{
		pair<int, int> coord;

		istringstream stream(inStr);

		stream >> coord.first >> coord.second;

		coords.push_back(coord);
	}

	return coords;
}

long long countVecMult(int x1, int y1, int x2, int y2)
{
	return (x1 * y2) - (x2 * y1);
}

int main()
{
	int counter = 0;

	auto coords = InitCoords();

	pair<int, int> firstCoord, secondCoord, thirdCoord;

	if (coords.size() < 3)
	{
		cout << 0;
		return 0;
	}

	firstCoord = coords[0];
	secondCoord = coords[1];
	thirdCoord = coords[2];

	int x1, y1, x2, y2;

	for (size_t i = 2; i < coords.size() - 1; i++)
	{
		x1 = secondCoord.first - firstCoord.first;
		y1 = secondCoord.second - firstCoord.second;

		x2 = thirdCoord.first - secondCoord.first;
		y2 = thirdCoord.second - secondCoord.second;

		auto mult = countVecMult(x1, y1, x2, y2);

		if (mult > 0)
		{
			counter++;
		}

		firstCoord = secondCoord;
		secondCoord = thirdCoord;
		thirdCoord = coords[i + 1];
	}

	x1 = secondCoord.first - firstCoord.first;
	y1 = secondCoord.second - firstCoord.second;

	x2 = thirdCoord.first - secondCoord.first;
	y2 = thirdCoord.second - secondCoord.second;

	auto mult = countVecMult(x1, y1, x2, y2);

	if (mult > 0)
	{
		counter++;
	}

	std::cout << counter << std::endl;

	return 0;
}
