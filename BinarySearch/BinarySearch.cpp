#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

typedef std::vector<int> VectorOfInts;
typedef std::set<int> SetOfInts;

void sortArrayOfData(VectorOfInts &arrayOfData)
{
	std::sort(arrayOfData.begin(), arrayOfData.end(), [&](int first, int second)->bool {
		return first < second;
	});
}

VectorOfInts readDataFromFile(const std::string &fileName)
{
	std::ifstream input(fileName);

	SetOfInts alreadyIncludedNumbers;
	VectorOfInts arrayOfData;
	while (!input.eof())
	{
		int element = 0;
		input >> element;

		bool doesAlreadyExists = alreadyIncludedNumbers.find(element) != alreadyIncludedNumbers.end();
		if (!doesAlreadyExists)
		{
			arrayOfData.push_back(element);
			alreadyIncludedNumbers.insert(element);
		}
	}

	return arrayOfData;
}

VectorOfInts initBinarySearch(const std::string &fileName)
{
	VectorOfInts arrayOfData = readDataFromFile(fileName);
	sortArrayOfData(arrayOfData);
	return arrayOfData;
}

int findElementIndex(int serachElement, VectorOfInts &arrayOfData)
{
	int left = 0;
	int right = arrayOfData.size() - 1;
	int key = -1;
	int middle = 0;

	while (left <= right)
	{
		middle = (left + right) / 2;

		if (serachElement < arrayOfData[middle])
		{
			right = middle - 1;
		}
		else if (serachElement > arrayOfData[middle])
		{
			left = middle + 1;
		}
		else
		{
			key = middle;
			break;
		}
	}

	return key;
}

void printExisitingData(VectorOfInts &arrayOfData)
{
	for (size_t i = 0; i < arrayOfData.size(); i++)
	{
		std::cout << i << " element: " << arrayOfData[i] << std::endl;
	}
}

void handleSearching(VectorOfInts &arrayOfData)
{
	int element;
	std::cin >> element;
	std::cout << "Element index is: " << findElementIndex(element, arrayOfData) << std::endl;
}

void eraseElement(VectorOfInts &arrayOfData)
{
	int element;
	std::cin >> element;
	
	int index = findElementIndex(element, arrayOfData);
	if (index != -1)
	{
		arrayOfData.erase(arrayOfData.begin() + index);
		std::cout << "Element removed " << std::endl;
	}
	else
	{
		std::cout << "Element not defined " << std::endl;
	}
}

void addNewElement(VectorOfInts &arrayOfData)
{
	int element = 0;
	std::cin >> element;

	int elementIndex = findElementIndex(element, arrayOfData);
	
	if (elementIndex != -1)
	{
		std::cout << "Element exists" << std::endl;
		return;
	}

	int left = 0;
	int right = arrayOfData.size() - 1;
	int key = -1;
	int middle = 0;

	while (left <= right)
	{
		middle = (left + right) / 2;

		if (element < arrayOfData[middle])
		{
			right = middle - 1;
		}
		else if (element > arrayOfData[middle])
		{
			left = middle + 1;
		}
		else
		{
			break;
		}
	}

	if (arrayOfData[middle] < element)
	{
		arrayOfData.insert((arrayOfData.begin() + (middle + 1)), element);
	}
	else
	{
		arrayOfData.insert((arrayOfData.begin() + (middle)), element);
	}
}

void printHelp()
{
	std::cout << "* Use 'findElement' to find the element" << std::endl;
	std::cout << "* Use 'removeElement' to removethe element" << std::endl;
	std::cout << "* Use 'printAll' to print the elements" << std::endl;
	std::cout << "* Use 'addNew' to add an element" << std::endl;
}

void binarySearching(const std::string &fileName)
{
	std::string state = "";

	VectorOfInts data = initBinarySearch(fileName);

	while (state != "end")
	{
		std::cin >> state;

		if (state == "help")
		{
			printHelp();
		}

		if (state == "findElement")
		{
			handleSearching(data);
		}

		if (state == "removeElement")
		{
			eraseElement(data);
		}

		if (state == "printAll")
		{
			printExisitingData(data);
		}

		if (state == "addNew")
		{
			addNewElement(data);
		}
	}
}

int main()
{
	const std::string fileName = "input.txt";
	binarySearching(fileName);
}