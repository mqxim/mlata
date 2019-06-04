#include <vector>
#include <istream>
#include <fstream>

// Ильин Максим, ПС-21

//  19.6.Змейка(3)

//  Змей Горыныч убедительно просит расположить N 2 чисел от 1 до N 2 в квадрате змейкой.
//  Ввод.В единственной строке файла INPUT.TXT задано число N(1 ≤ N ≤ 50).
//  Вывод.Файл OUTPUT.TXT содержит N 2 чисел по N чисел в строке в форме змейки.

using namespace std;

using Map = vector<vector<int>>;

Map CreateMap(const size_t q)
{
	Map vec(q);

	for (size_t i = 0; i < q; ++i)
	{
		vec[i] = vector<int>(q, 0);
	}

	return vec;
}

void PrintSnake(ostream & fout, const size_t q)
{
	auto vec = CreateMap(q);

	bool moveToTop = false;

	size_t x = 0;
	size_t y = 0;
	
	size_t v = 1;

	while (v <= q * q)
	{
		do
		{
			if (moveToTop && x > 0)
			{
				x--;
				y++;
			}
			else if (y > 0)
			{
				x++;
				y--;
			}

			if (x < q && y < q)
			{
				vec[y][x] = v;
				v++;
			}

		} while (x != 0 && y != 0);

		if (y == 0 || y == q - 1)
		{
			x++;
		}
		else if (x == 0 || x == q - 1)
		{
			y++;
		}

		if (x < q && y < q)
		{
			vec[y][x] = v;
			v++;
		}

		moveToTop = !moveToTop;
	}

	for (auto& i : vec)
	{
		for (auto& g : i)
		{
			fout << g << ' ';
		}

		fout << '\n';
	}

}

int main()
{
	ifstream fin("input.txt");

	ofstream fout("output.txt");

	int n = 0;

	fin >> n;

	PrintSnake(fout, n);

	return 0;
}