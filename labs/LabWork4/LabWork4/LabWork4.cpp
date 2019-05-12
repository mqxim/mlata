#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>

using td = long long;

std::string inName;

struct Line2
{
	Line2(td value, bool isStart) : value(value), isStart(isStart)
	{
	}

	td value;
	bool isStart = false;
};

struct Info
{
	Info(td quantityLines, td minNesting) : quantityLines(quantityLines), minNesting(minNesting)
	{
	}

	td quantityLines, minNesting;

	td min = UINT_MAX;

	td max = 0;

	std::vector<Line2> vals;
};

Info InitLines()
{
	std::ifstream input(inName);

	if (input.bad())
	{
		return Info(0, 0);
	}

	std::string inStr;

	int quantityLines, minNesting;

	std::getline(input, inStr);

	std::istringstream sstream(inStr);

	sstream >> quantityLines >> minNesting;

	Info info(quantityLines, minNesting);

	std::vector<Line2> lines;

	std::vector<Line2> linesend;

	unsigned int start, end;

	while (std::getline(input, inStr))
	{
		std::istringstream sstream(inStr);

		sstream >> start >> end;

		if (start < info.min)
		{
			info.min = start;
		}

		if (end > info.max)
		{
			info.max = end;
		}

		lines.push_back(Line2(start, true));
		linesend.push_back(Line2(end, false));
	}

	for (size_t i = 0; i < linesend.size(); i++)
	{
		lines.push_back(linesend[i]);
	}

	std::sort(lines.begin(), lines.end(), [](const Line2& l1, const Line2& l2)->bool {
		return (l1.value < l2.value);
	});

	info.vals = lines;

	return info;
}

void findQ(Info& inf)
{

	td quantity = 0;
	td nesting = 0;
	td lastNesting = 0;

	for (auto i = inf.vals.begin(); i != inf.vals.end(); i++)
	{
		if (i->isStart)
		{
			nesting++;
		}
		else
		{
			nesting--;
		}

		if (nesting == inf.minNesting)
		{
			if (lastNesting + 1 == inf.minNesting)
			{
				quantity++;
			}
		}

		lastNesting = nesting;
	}

	std::cout << quantity << std::endl;
}

int main(int argc, char* argv[])
{
	inName = argv[1];
	Info l = InitLines();
	findQ(l);
	return 0;
}