#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using Coord = std::pair<int, int>;

using Coords = std::vector<std::pair<int, int>>;

using Field = std::vector<std::vector<int>>;

Coords GetCoords()
{
	Coords coords;

	std::string str;

	while (std::getline(std::cin, str))
	{
		int x, y;

		std::istringstream stream(str);

		stream >> x >> y;

		std::pair<int, int> pair(x - 1, y - 1);

		coords.push_back(pair);
	}

	return coords;
}

Field CreateField(int size)
{
	if ((size < 0) || (size > 500))
	{
		throw std::exception("Too big field");
	}

	std::vector<std::vector<int>> matrix;

	for (int i = 0; i < size; i++)
	{
		std::vector<int> vec(size, -1);
		
		matrix.push_back(vec);
	}

	return matrix;
}

Coords MarkCurrentCoordsAndGetNext(Field& field, const Coords& coords, int value)
{
	Coords newCoords;

	for (auto& coord : coords)
	{
		if (coord.second >= int(field.size()) || coord.first >= int(field.size()) || coord.second < 0 || coord.first < 0)
		{
			continue;
		}

		if (field[coord.second][coord.first] != -1)
		{
			continue;
		}

		field[coord.second][coord.first] = value;

		Coord c1(coord.first + 1, coord.second);
		Coord c2(coord.first - 1, coord.second);
		Coord c3(coord.first, coord.second + 1);
		Coord c4(coord.first, coord.second - 1);

		newCoords.push_back(c1);
		newCoords.push_back(c2);
		newCoords.push_back(c3);
		newCoords.push_back(c4);
	}

	return newCoords;
}

int GetQuantityOfTurns(int sizeOfField, Coords& coords)
{
	Field field = CreateField(sizeOfField);

	int markValue = 0;

	Coords newCoords = coords;

	do
	{
		newCoords = MarkCurrentCoordsAndGetNext(field, newCoords, markValue);
		markValue++;
	}
	while (!newCoords.empty());

	int max = 0;

	for (auto& line : field)
	{
		auto maxNew = std::max_element(line.begin(), line.end());

		if (*maxNew > max)
		{
			max = *maxNew;
		}
	}

	return max;
}

int main()
{
	int fieldSize = 0; std::cin >> fieldSize;

	Coords coords = GetCoords();

	std::cout << GetQuantityOfTurns(fieldSize, coords) << std::endl;

	return 0;
}