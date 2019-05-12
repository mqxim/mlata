#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using Map = std::vector<std::vector<int>>;

using Seen = std::vector<std::pair<int, int>>;

int m, n;


Map ReadMap()
{
	std::cin >> m >> n;

	Map map;

	for (int i = 0; i < m; i++)
	{
		std::vector<int> line;

		for (int g = 0; g < n; g++)
		{
			char value;

			std::cin >> value;

			if (value == '#')
			{
				line.push_back(1);
			}
			else
			{
				line.push_back(0);
			}
		}

		map.push_back(line);
	}

	return map;
}

int RecursiveSearch(int q, Map& map, Seen seen, int x, int y)
{
	if (y >= map.size())
	{
		return q;
	}

	if (x >= map[y].size())
	{
		return q;
	}

	bool found = false;

	std::for_each(seen.begin(), seen.end(), [&](std::pair<int, int>& pair) {
		if ((pair.first == x) && (pair.second == y))
		{
			found = true;
		}
	});

	if (found)
	{
		return q;
	}

	if (map[y][x] == 1)
	{
		q++;

		seen.push_back(std::pair<int, int >(x, y));

		int q1 = RecursiveSearch(q, map, seen, x + 1, y);
		
		int q2 = RecursiveSearch(q, map, seen, x, y + 1);

		int q3 = RecursiveSearch(q, map, seen, x - 1, y);

		int q4 = RecursiveSearch(q, map, seen, x, y - 1);

		std::array<int, 4> ar = { q1, q2, q3, q4 };

		return *std::max_element(ar.begin(), ar.end());
	}

	return q;
}

int GetMaxQ(Map& map)
{
	std::vector<std::pair<int, int>> seen;

	int maxQ = 0;

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t g = 0; g < map[i].size(); g++)
		{
			int q0 = 0;
			int q = RecursiveSearch(q0, map, seen, g, i);

			if (q > maxQ)
			{
				maxQ = q;
			}

			seen.clear();
		}
	}

	return maxQ;
}

int main()
{
	Map map = ReadMap();
	
	std::cout << GetMaxQ(map) << std::endl;

	return 0;
}