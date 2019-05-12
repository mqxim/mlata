#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

const int MAX_SIZE = 100;
const char FIELD_SIGN = '#';

struct MapInfo
{
	int height;
	int width;

	bool visitedFields[MAX_SIZE][MAX_SIZE] = {};
	int fieldValues[MAX_SIZE][MAX_SIZE] = {};
	
	std::ifstream inputStream;
};

void setMapDefaultValues(MapInfo &mapInfo)
{
	int currentLine = 0;
	
	std::string line;
	std::getline(mapInfo.inputStream, line);

	while (!mapInfo.inputStream.eof())
	{
		std::string line;
		std::getline(mapInfo.inputStream, line);

		for (size_t i = 0; i < line.length(); i++)
		{
			if (line[i] == FIELD_SIGN)
			{
				mapInfo.fieldValues[currentLine][i] = 1;
			}
			else
			{
				mapInfo.fieldValues[currentLine][i] = 0;
			}

			mapInfo.visitedFields[currentLine][i] = false;
		}

		currentLine++;
	}
}

MapInfo initializeMap()
{
	MapInfo info;
	
	info.inputStream.open("input.txt");
	info.inputStream >> info.width;
	info.inputStream >> info.height;

	if ((info.width > MAX_SIZE) || (info.height > MAX_SIZE))
	{
		throw std::invalid_argument("Too bog field");
	}

	setMapDefaultValues(info);
	
	return info;
}

void showMap(MapInfo &map)
{
	for (size_t i = 0; i < map.width; i++)
	{
		for (size_t g = 0; g < map.height; g++)
		{
			std::cout << map.fieldValues[i][g];
		}
		std::cout << std::endl;
	}
}

void markFields(MapInfo &map, int posX, int posY, bool &found)
{
	if ((posX < 0) || (posY < 0))
	{
		return;
	}

	if ((map.fieldValues[posX][posY] == 1) && (!map.visitedFields[posX][posY]))
	{
		found = true;
		map.visitedFields[posX][posY] = true;
		markFields(map, posX - 1, posY, found);
		markFields(map, posX + 1, posY, found);
		markFields(map, posX, posY - 1, found);
		markFields(map, posX, posY + 1, found);
	}
}

bool markNearFields(MapInfo &map, int posX, int posY)
{
	bool mark = false;
	markFields(map, posX, posY, mark);
	return mark;
}

void printFieldsQuantity(MapInfo &map)
{
	int fieldsQ = 0;
	for (int i = 0; i < map.width; i++)
	{
		for (int g = 0; g < map.height; g++)
		{
			if (markNearFields(map, i, g))
			{
				fieldsQ++;
			}
		}
	}

	std::cout << fieldsQ << std::endl;
}

int main()
{	
	MapInfo map = initializeMap();
	showMap(map);
	printFieldsQuantity(map);
	
	return 0;
}