#include "pch.h"
#include <iostream>
#include <array>
#include <fstream>
#include <climits>

const int MAX_SIZE = 100;

typedef std::array<std::array<int, MAX_SIZE>, MAX_SIZE> Map;

struct MapInfo
{
	Map map = { 0 };
	Map weights = { { INT_MAX} };
	int width = 0;
	int height = 0;
	int startX = 0;
	int startY = 0;
	int finishX = 0;
	int finishY = 0;
};

MapInfo initMap(std::ifstream &input)
{
	MapInfo mapInfo;

	input >> mapInfo.height >> mapInfo.width;
	
	for (int i = 0; i < mapInfo.height; i++)
	{
		for (int g = 0; g < mapInfo.width; g++)
		{
			int number;
			input >> number;
			mapInfo.map[i][g] = number;
			mapInfo.weights[i][g] = INT_MAX;
		}
	}
	
	mapInfo.finishX = mapInfo.width - 1;
	mapInfo.finishY = mapInfo.height - 1;

	std::cout << mapInfo.finishX << "  " << mapInfo.finishY << std::endl;
	
	return mapInfo;
}


void findTheWay(MapInfo &map, int startX, int startY, int lastSum)
{
	lastSum = lastSum + map.map[startY][startX];

	if (lastSum < map.weights[startY][startX])
	{
		map.weights[startY][startX] = lastSum;
	}

	if ((startX + 1 <= map.finishX) && (startY + 1 <= map.finishY))
	{
		findTheWay(map, startX + 1, startY + 1, lastSum);
	}

	if ((startX <= map.finishX) && (startY + 1 <= map.finishY))
	{
		findTheWay(map, startX, startY + 1, lastSum);
	}

	if ((startX + 1 <= map.finishX) && (startY <= map.finishY))
	{
		findTheWay(map, startX + 1, startY, lastSum);
	}
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	MapInfo map = initMap(input);
	findTheWay(map, 0, 0, 0);

	int x = map.finishX;
	int y = map.finishY;
	std::cout << map.weights[49][49] << std::endl;

	return 0;
}