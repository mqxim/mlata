#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

std::vector<int> vec;

void add(size_t el, int v)
{
	for (size_t i = el; i < vec.size(); i = i | (i + 1))
	{
		vec[i] += v;
	}
}

void init()
{
	std::vector<int> vec2;

	int n;

	string str;

	getline(cin, str);

	istringstream stream(str);

	while (stream >> n)
	{
		vec2.push_back(n);
	}

	vec = std::vector<int>(vec2.size(), 0);

	for (size_t i = 0; i < vec2.size(); ++i)
	{
		add(i, vec2[i]);
	}
}

int rsq(int f, int l)
{
	int result = 0;

	for (int i = f - 1; i >= 0; i = (i & (i + 1)) - 1)
	{
		result += vec[i];
	}

	int result2 = 0;
	for (int i = l; i >= 0; i = (i & (i + 1)) - 1)
	{
		result2 += vec[i];
	}

	return result2 - result;
}

void update(int el, int v)
{
	add(el, v - rsq(el, el));
}

int main()
{
	init();

	string str;

	while (getline(cin, str))
	{
		std::istringstream stream(str);

		string command;

		int f, l;

		stream >> command >> f >> l;


		if (command == "rsq")
		{
			cout << "rsq(" << f << ", " << l << ") = " << rsq(f, l) << endl;
		}
		else if (command == "add")
		{
			add(f, l);
		}
		else if (command == "update")
		{
			update(f, l);
		}
		else if (command == "exit")
		{
			break;
		}
	}

	return 0;
}
