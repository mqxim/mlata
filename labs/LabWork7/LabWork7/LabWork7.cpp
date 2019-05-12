#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int quantity;

vector<int> graf, sorted, wasSeen;

vector<vector<int>> matr;

vector<bool> visited;

vector<int> ans;

void ReadQuantity()
{
	string inStr;
	getline(cin, inStr);
	istringstream stream(inStr);
	stream >> quantity;
}

void InitData()
{
	ReadQuantity();

	vector<bool> visit;

	vector<vector<int>> matrix;
	
	vector<int> seenBefore(quantity);

	for (int i = 0; i < quantity; i++)
	{
		vector<int> row;

		for (int j = 0; j < quantity; j++)
		{
			row.push_back(0);
			visit.push_back(false);
		}
		matrix.push_back(row);
	}

	string inStr;

	int rowNum = 0;

	while (getline(cin, inStr))
	{
		istringstream stream(inStr);

		int pos = 0;

		int value = 0;

		while (stream >> value)
		{
			if (pos == 0)
			{
				seenBefore.push_back(value);
			}
			else
			{
				matrix[rowNum][value - 1] = 1;
			}
			pos++;
		}

		rowNum++;
	}
	
	matr = matrix;
	visited = visit;
	wasSeen = seenBefore;
}

void sort2()
{
	vector<int> seen;

	for (size_t g = 0; g < matr.size(); g++)
	{
		for (size_t i = 0; i < matr.size(); i++)
		{
			bool isZero = true;

			for (size_t j = 0; j < matr.size(); j++)
			{
				if (matr[i][j] != 0)
				{
					isZero = false;
				}
			}

			if (isZero)
			{
				auto ptr = std::find(seen.begin(), seen.end(), i);
				
				if (ptr == seen.end())
				{
					seen.push_back(i);
				}

				for (size_t j = 0; j < matr.size(); j++)
				{
					matr[j][i] = 0;
				}
			}
		}
	}

	for (size_t i = 0; i < seen.size(); i++)
	{
		cout << seen[i] + 1 << endl;
	}
}

int main()
{
	InitData();
	sort2();
}