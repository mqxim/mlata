#pragma once
#include <string>
#include "constants.hpp"

struct Operand
{
	std::string term;
	Operation unaryOperation = EMPTY_OPERATION;
};

struct ExpressionData
{
	Operand left;
	Operand right;
	Operation operation = EMPTY_OPERATION;
	bool isValid;
};

ExpressionData selectOperands(std::string expression);
