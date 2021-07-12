#include <iostream>
#include <climits>
#include <fstream>
#include <vector>

using namespace std;

struct GraphInfo
{
    size_t matrixSize;
    int mainNode;
};

struct MatrixNode
{
	int from;
	int to;
	int weight;
	bool isGoodNode;
};

ifstream createInputStream()
{
	string fileName;

	cout << "Enter file name:" << endl;
	cin >> fileName;
	ifstream inputStream(fileName);
	return inputStream;
}

GraphInfo getMatrixInfo(ifstream &input)
{
	size_t size;
    int mainNode;
	input >> size >> mainNode;
	cout << "Size:" << size << endl;
    cout << "Main node: " << mainNode << endl;

    GraphInfo info;
    info.mainNode = mainNode - 1;
    info.matrixSize = size;
	return info;
}

MatrixNode getNode(ifstream &input, int matrixSize)
{
	MatrixNode node;
    int from;
    int to;
    int weight;
	
    input >> from >> to >> weight;

	bool isMoreThanZero = (from > 0) && (to > 0) && (weight > 0);
	bool isLessThanSize = (to <= matrixSize) && (from <= matrixSize);

	if (!(isMoreThanZero && isLessThanSize))
	{
		node.isGoodNode = false;
	}
	else
	{
		node.isGoodNode = true;
        node.from = from - 1;
        node.to = to - 1;
        node.weight = weight;
	}
	return node;
}

void updateState(int x, int y, vector<string> &info, int weight)
	{
		x = x + 1;
		y = y + 1;
		string result = to_string(x) + '-' + to_string(y) + ' ' + to_string(weight);
		info.push_back(result);
		cout << "New: " << x << '-' << y << endl;
	}

void printState(int weight, bool wasChecked)
{
    if (weight == INT_MAX)
    {
        cout << "inf";
    }
    else
    {
        if (wasChecked)
        {
            cout << "(";
        }
		cout << weight;
		if (wasChecked)
		{
			cout << ")";
		}
    }
	cout << "   ";
}

int main()
{
    ifstream input = createInputStream();
    GraphInfo matrixInfo = getMatrixInfo(input);
	size_t matrixSize = matrixInfo.matrixSize;
	int main = matrixInfo.mainNode;
    int smallest;
	int currX;
	int currY;
	vector<string> info = {};
	int sum = 0;
	int weights[matrixSize] = {};
	std::fill_n(weights, matrixSize, INT_MAX);
	weights[main] = 0;
	
	bool checkedValues[matrixSize] = {};
	checkedValues[main] = true;
	
	int getFrom[matrixSize] = {};
	getFrom[main] = 0;

	int matrix[matrixSize][matrixSize] = {};
	int result[matrixSize][matrixSize] = {};

    while (!input.eof())
	{
		MatrixNode node = getNode(input, matrixSize);
		if (node.isGoodNode)
		{
			matrix[node.from][node.to] = node.weight;
			matrix[node.to][node.from] = node.weight;		
		}
	}

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][j] = INT_MAX;
            }    
        }
    }

    while (smallest != INT_MAX)
    {
        smallest = INT_MAX;

        for (int j = 0; j < matrixSize; j++)
        {
            bool isLessThanWeights = matrix[main][j] < weights[j];
			bool notChecked = !checkedValues[j];
			bool notInf = matrix[main][j] != INT_MAX;

            if (notInf && notChecked && isLessThanWeights)
            {
				weights[j] = matrix[main][j];
				getFrom[j] = main;
            }
			if (notChecked && (weights[j] < smallest))
			{
				currY = getFrom[j];
				currX = j;
				smallest = weights[j];
			}
			printState(weights[j], checkedValues[j]);
		}	

        if (smallest != INT_MAX)
        {
            main = currX;
            result[currX][currY] = smallest;
            result[currY][currX] = smallest;
            checkedValues[currX] = true;
			sum = sum + weights[main];
			updateState(currX, currY, info, weights[main]);
		}		
    }	

	cout << endl << "SUM: " << sum << endl ;

	for (auto i = info.begin(); i != info.end(); i++)
	{
		cout << *i << endl;
	}
}