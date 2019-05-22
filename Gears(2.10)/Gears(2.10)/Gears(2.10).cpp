#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Ильин М., ПС-21

//  2.10.Шестеренки(7)
//  Имеется система сцепленных шестеренок, пронумерованных от 1 до N.Заданы пары номеров
//  сцепленных шестеренок.Первая должна двигаться по часовой стрелке.Определить характер
//  движения всех шестеренок.
 
//  Варианты движения :
//  clockwise - по часовой;
//  unclockwise - против;
//  immovable - шестеренка неподвижна;
//  block - заклинивание.

enum class Direction : int
{
	Clockwise,
	Unclockwise,
	Immovable,
};

Direction opposite(Direction dir)
{
	switch (dir)
	{
	case Direction::Clockwise:
		return Direction::Unclockwise;
	case Direction::Unclockwise:
		return Direction::Clockwise;
	default:
		return Direction::Immovable;
	}
}

std::string toString(Direction dir)
{
	switch (dir)
	{
	case Direction::Clockwise:
		return "clockwise";
	case Direction::Unclockwise:
		return "unclockwise";
	case Direction::Immovable:
		return "immovable";
	}
}

int main()
{
	std::ifstream fin("input.txt");
	
	std::ofstream fout("output.txt");

	int n, m;
	
	fin >> n >> m;

	vector<vector<int>> edges(n);
	
	for (int i = 0; i < m; i++)
	{
		int x, y;
		
		fin >> x >> y;
		
		x--;
		
		y--;
		
		edges[x].push_back(y);
		
		edges[y].push_back(x);
	}

	vector<Direction> dirs(n, Direction::Immovable);

	dirs[0] = Direction::Clockwise;

	queue<int> q;

	q.push(0);

	while (!q.empty())
	{
		int i = q.front();

		q.pop();

		Direction dir = opposite(dirs[i]);

		for (int j = 0; j < edges[i].size(); j++)
		{
			int k = edges[i][j];
			
			if (dirs[k] == Direction::Immovable)
			{
				dirs[k] = dir;
				q.push(k);
			}
			else if (dirs[k] != dir)
			{
				fout << "blocked" << endl;
				return 0;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		fout << toString(dirs[i]) << endl;
	}

	return 0;
}