#include <string>
#include <iostream>
#include "binaryTree.hpp"

int main()
{
    std::string input;
	std::getline(std::cin, input);
	printExpressionTree(input);
    return 0;
}