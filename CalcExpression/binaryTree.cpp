#include <iostream>
#include <string>
#include "binaryTree.hpp"
#include "selectOperands.hpp"

struct Node;
typedef Node *ptr;
struct Node
{
	Operation operation = EMPTY_OPERATION;
	std::string operand;

	ptr left = nullptr;
	ptr right = nullptr;	
};

void buildExpressionTree(ptr &pointer,  std::string &expression)
{
	ExpressionData expressionData = selectOperands(expression);
	if (!expressionData.isValid)
	{
		return;
	}
	if (pointer == nullptr)
	{
		pointer = new Node;
		if (expressionData.operation != EMPTY_OPERATION)
		{
			pointer->operation = expressionData.operation;
			buildExpressionTree(pointer->left, expressionData.left.term);
			buildExpressionTree(pointer->right, expressionData.right.term);
		}
		else
		if (expressionData.left.unaryOperation != EMPTY_OPERATION)
		{
			pointer->operation = expressionData.left.unaryOperation;
			buildExpressionTree(pointer->left, expressionData.left.term);
		}
		else
		{
			pointer->left = new Node;
			pointer->left->operand = expressionData.left.term;
			
			pointer->right = new Node;
			pointer->right->operand = expressionData.right.term;
		}
	}
}

void printTree(ptr pointer)
{
	if (pointer == nullptr)
	{
		return;
	}
	
	printTree(pointer->left);
	printTree(pointer->right);

	if (pointer->operation != EMPTY_OPERATION)
	{
		std::cout << pointer->operation;
	}
	else
	{
		std::cout << pointer->operand;
	}
}

void destroyTree(ptr &pointer)
{
	if (pointer)
	{
		destroyTree(pointer->left);
		destroyTree(pointer->right);
		delete pointer;
		pointer = nullptr;
	}
}

void printExpressionTree(std::string expression)
{
	ptr root = nullptr;
	buildExpressionTree(root, expression);
	printTree(root);
	destroyTree(root);
}
