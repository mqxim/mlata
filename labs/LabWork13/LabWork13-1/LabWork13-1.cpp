#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>

std::vector<int> vecOfNumbers;

std::vector<int> tree;

void initTree(int i, int L, int R)
{
	if (L == R)
	{
		tree[i] = vecOfNumbers[L];
	}
	else
	{
		int m = (L + R) / 2;

		initTree(2 * i, L, m);

		initTree(2 * i + 1, m + 1, R);

		tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
	}
}

void build()
{
	int n;

	vecOfNumbers.push_back(0);

	std::string str;

	std::getline(std::cin, str);

	std::istringstream stream(str);

	while (stream >> n)
	{
		vecOfNumbers.push_back(n);
	}

	tree = std::vector<int>((vecOfNumbers.size() - 1) * 4);

	initTree(1, 1, vecOfNumbers.size() - 1);
}

int rmq(int L, int R, int i, int Tl, int Tr)
{
	if (L == Tl && R == Tr)
	{
		return tree[i];
	}
	else
	{
		int m = (Tl + Tr) / 2;

		if (R <= m)
		{
			return rmq(L, R, 2 * i, Tl, m);
		}
		
		if (L > m)
		{
			return rmq(L, R, 2 * i + 1, m + 1, Tr);
		}
		
		return std::max(rmq(L, m, 2 * i, Tl, m), rmq(m + 1, R, 2 * i + 1, m + 1, Tr));
	}
}


void add1(int id, int val, int i, int L, int R)
{
	if (L == R)
	{
		tree[i] += val;
	}
	else
	{
		int m = (L + R) / 2;

		if (id <= m)
		{
			add1(id, val, 2 * i, L, m);
		}
		else
		{
			add1(id, val, 2 * i + 1, m + 1, R);
		}

		tree[i] = std::max(tree[2 * i], tree[2 * i + 1]);
	}
}


void add2(int v, int tl, int tr, int l, int r, int add) {
	if (l > r)
	{
		return;
	}

	if (l == tl && tr == r)
	{
		tree[v] += add;
	}
	else
	{
		int tm = (tl + tr) / 2;
	
		add2(v * 2, tl, tm, l, std::min(r, tm), add);
		
		add2(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, add);
	}
}

int main()
{
	std::string str;

	build();

	int a, b;

	while (std::cin >> str >> a >> b)
	{
		if (str == "rmq")
		{
			std::cout << "rmq(" << a << ", " << b << ") = " << rmq(a, b, 1, 1, vecOfNumbers.size() - 1) << std::endl;
		}

		if (str == "add1")
		{
			add1(a, b, 1, 1, vecOfNumbers.size() - 1);
		}

		if (str == "add2")
		{
			int c;

			std::cin >> c;
			
			add2(1, 1, vecOfNumbers.size() - 1, a, b, c);
		}
	}

	return 0;
}