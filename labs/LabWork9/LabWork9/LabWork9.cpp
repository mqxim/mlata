#include "pch.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<char, int> CreateMapOfWordChars(const string& word)
{
	map<char, int> map;

	for (auto ch : word)
	{
		auto iter = map.find(ch);

		if (iter == map.end())
		{
			pair<char, int> pair(ch, 1);

			map.insert(pair);
		}
		else
		{
			iter->second++;
		}
	}

	return map;
}

int GetQuantityOfWordsThatCanBeCreated(map<char, int>& mainWord)
{
	int q = 0;

	string str;

	map<int, map<string, int>> words;

	while (getline(cin, str))
	{
		auto wordChars = CreateMapOfWordChars(str);
	
		bool canBeCreated = true;

		for (auto pair : wordChars)
		{
			auto iter = mainWord.find(pair.first);
		
			if ((iter == mainWord.end()) || (iter->second < pair.second))
			{
				canBeCreated = false;
			}

			if (!canBeCreated)
			{
				break;
			}
		}

		if (canBeCreated)
		{
			q = q + str.length();
		
			auto iter = words.find(str.length());

			if (iter == words.end())
			{
				pair<string, int> mapstrint(str, 1);
				pair<int, map<string, int>> pair;
				pair.first = str.length();
				pair.second.insert(mapstrint);
				words.insert(pair);
			}
			else
			{
				auto ptr = iter->second.find(str);

				if (ptr == iter->second.end())
				{
					pair<string, int> para(str, 1);
					iter->second.insert(para);
				}
				else
				{
					ptr->second++;
				}
			}
		}
	}

	std::cout << q << std::endl;

	for (auto i = words.rbegin(); i != words.rend(); i++)
	{
		for (auto& p : (*i).second)
		{
			for (int i = 0; i < p.second; i++)
			{
				std::cout << p.first << std::endl;;
			}
		}
	}

	return q;
}

int main()
{
	std::string word;

	std::getline(std::cin, word);

	auto map = CreateMapOfWordChars(word);

	GetQuantityOfWordsThatCanBeCreated(map);

	return 0;
}