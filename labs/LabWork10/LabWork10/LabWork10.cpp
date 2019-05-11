#include "pch.h"
#include <iostream>

int main()
{
	int m;
	std::cin >> m;

	for (int i = 0; i < m; i++)
	{
		int x, y;

		std::cin >> x >> y;
	
		if ((x % 2 == 0) || (y % 2 == 0))
		{
			std::cout << 1 << std::endl;
		}
		else
		{
			std::cout << 2 << std::endl;
		}
	}
}