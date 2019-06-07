#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <fstream>

//Ильин М., ПС-21

//3.7.Эксперимент(6)

//Результат эксперимента представляет собой матрицу из N × M(1 ≤ N, M≤ 2000),
//заполненную целыми числами, по модулю не превосходящими 500. Отвечающим условиям
//
//эксперимента считаются такие подматрицы размера K строк и L столбцов(0 & lt; K& lt; N, 0 & lt; L& lt;
//M), что сумма элементов в каждой из них в точности равна заданному числу S.
//Определить, сколько подматриц в исходной матрице отвечают условиям эксперимента.
//Ввод.В первой строке файла INPUT.TXT находятся 5 чисел N, M, K, L и S, разделенных
//пробелами.В каждой из следующих N строк находятся через пробел по M чисел, являющихся
//элементами матрицы.
//Вывод.В первой строке файла OUTPUT.TXT вывести единственное число – количество
//подматриц размера K×L, сумма элементов в которых равна S.

using namespace std;

struct MetaData
{
	MetaData() : n(0), m(0), k(0), l(0), s(0)
	{
	}

	int n, m, k, l, s;
};

MetaData GetMetaData(const string& str)
{
	MetaData md;

	istringstream fin(str);
	fin >> md.n >> md.m >> md.k >> md.l >> md.s;
	
	return md;
}

vector<int> SelectNumbersFromRow(const string& str, int q)
{
	istringstream fin(str);

	vector<int> vecOfNms;

	int num;

	for (int i = 0; i < q; ++i)
	{
		fin >> num;

		vecOfNms.push_back(num);
	}

	return vecOfNms;
}

vector<int> SelectRowSumsFromStr(const string& str, int matrixLength, int q)
{
	auto nums = SelectNumbersFromRow(str, q);

	int first = 0, sum = 0;

	vector<int> vecOfSums;

	for (int i = 0; i < int(nums.size()); ++i)
	{
		sum += nums[i];

		if (i >= matrixLength - 1)
		{
			vecOfSums.push_back(sum);
			sum -= nums[first++];
		}
	}

	return vecOfSums;
}

int main()
{
	ifstream fin("input.txt");

	ofstream fout("output.txt");

	string str;

	getline(fin, str);

	auto md = GetMetaData(str);

	std::vector<int> sums(md.m - md.l + 1, 0);

	queue<vector<int>> queue;
	
	int counter = 0;
	for (int i = 0; i < md.n; ++i)
	{
		getline(fin, str);

		auto s = SelectRowSumsFromStr(str, md.l, md.m);

		queue.push(s);

		if (i < md.k)
		{
			for (int g = 0; g < md.m - md.l + 1; g++)
			{
				sums[g] += s[g];
			}
			
		}
		else
		{
			auto front = queue.front();

			for (int g = 0; g < md.m - md.l + 1; g++)
			{
				if (sums[g] == md.s)
				{
					counter++;
				}
			
				sums[g] += s[g];
			
				sums[g] -= front[g];
			}

			queue.pop();
		}
	}

	for (int g = 0; g < md.m - md.l + 1; g++)
	{
		if (sums[g] == md.s)
		{
			counter++;
		}
	}

	fout << counter << endl;

	return 0;
}