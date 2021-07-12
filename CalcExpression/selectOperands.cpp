#include "selectOperands.hpp"
#include "operationsPriority.hpp"
#include "removeExtraBrackets.hpp"
#include "eraseBlanks.hpp"

typedef char State;
static const State START = 0;
static const State OPERAND = 1;
static const State OPERATION = 2;
static const State ERROR = 3;

static const std::string EMPTY_STRING = "";

struct ProcessingExpressionInfo
{
	ProcessingExpressionInfo(const std::string &expression) :
		expression(expression)
	{
	}

    int position = 0;
	std::string expression;

	std::string leftOperand;
	std::string rightOperand;

    Operation unaryOperation = EMPTY_OPERATION;
    Operation operation = EMPTY_OPERATION;

	bool wasLeftOperandChanged = false;
};

std::string getOperandWithBrackets(const std::string &expression, int &position)
{
	std::string result;
	int counter = 0;

	while (position < expression.length())
	{
		if (expression[position] == RIGHT_BRACKET)
		{
			counter--;
		}

		if (expression[position] == LEFT_BRACKET)
		{
			counter++;
		}

		result += expression[position];
		position++;

		if (counter == 0)
		{
			break;
		}
	}

	if (counter != 0)
	{
		return EMPTY_STRING;
	}

	return result;
}

std::string getSimpleOperand(const std::string &expression, int &position)
{
	std::string result;

	while (position < expression.length())
	{
		if (!isOperation(expression[position]))
		{
			result += expression[position];
			position++;
		}
		else
		{
			break;
		}
	}
	return result;
}

std::string getOperand(const std::string &expression, int &position)
{
    if (expression[position] == LEFT_BRACKET)
    {
		return getOperandWithBrackets(expression, position);
    }
    else
    {
		return getSimpleOperand(expression, position);
    }
}

Operation getOperation(const std::string &expression, int &position)
{
	if (isOperation(expression[position]))
	{
		position++;
		return expression[position - 1];
	}

	return EMPTY_OPERATION;
}

State handleStartState(ProcessingExpressionInfo &expressionInfo)
{
	expressionInfo.unaryOperation = getOperation(expressionInfo.expression, expressionInfo.position);
	return OPERAND;
}

State handleOperationState(ProcessingExpressionInfo &expressionInfo)
{
	Operation newOperation = getOperation(expressionInfo.expression, expressionInfo.position);
	
	if (newOperation == EMPTY_OPERATION)
	{
		return ERROR;
	}

	if (hasMorePriority(newOperation, expressionInfo.operation))
	{
		if (expressionInfo.operation != EMPTY_OPERATION)
		{
			expressionInfo.leftOperand += expressionInfo.operation;
		}
		expressionInfo.leftOperand += expressionInfo.rightOperand;
		
		expressionInfo.operation = newOperation;
		expressionInfo.rightOperand = EMPTY_STRING;
		expressionInfo.wasLeftOperandChanged = true;
	}
	else
	{
		expressionInfo.rightOperand += newOperation;
	}

	return OPERAND;
}

State handleOperandState(ProcessingExpressionInfo &expressionInfo)
{
	std::string operand = getOperand(expressionInfo.expression, expressionInfo.position);
	if (operand != EMPTY_STRING)
	{
		expressionInfo.rightOperand += operand;
	}
	else
	{
		return ERROR;
	}

	return OPERATION;
}

ExpressionData createResult(const ProcessingExpressionInfo &expressionInfo)
{
	ExpressionData data;
	Operand leftOperand;
	Operand rightOperand;

	leftOperand.term = expressionInfo.leftOperand;
	if (!expressionInfo.wasLeftOperandChanged)
	{
		leftOperand.unaryOperation = expressionInfo.unaryOperation;
	}
	else
	{
		if (expressionInfo.unaryOperation != EMPTY_OPERATION)
		{
			leftOperand.term = expressionInfo.unaryOperation + expressionInfo.leftOperand;
		}
	}

	if (expressionInfo.leftOperand == EMPTY_STRING)
	{
		leftOperand.term = expressionInfo.rightOperand;
	}
	else
	{
		rightOperand.term = expressionInfo.rightOperand;
	}
	
	data.left = leftOperand;
	data.right = rightOperand;
	data.operation = expressionInfo.operation;
	data.isValid = true;
	return data;
}

ExpressionData createBadResult()
{
	ExpressionData data;
	data.isValid = false;
	return data;
}

ExpressionData selectOperands(const std::string expression)
{
	std::string clearedExpression = removeExtraBrackets(eraseBlanks(expression));

	ProcessingExpressionInfo expressionInfo = ProcessingExpressionInfo(clearedExpression);

	State state = START;

    while (expressionInfo.position < clearedExpression.length())
    {
        if (state == START)
        {
			state = handleStartState(expressionInfo);
        }

        if (state == OPERATION)
        {
			state = handleOperationState(expressionInfo);
        }

        if (state == OPERAND)
        {
			state = handleOperandState(expressionInfo);
        }

		if (state == ERROR)
		{
			break;
		}
    }
	
	if (state != OPERATION)
	{
		return createBadResult();
	}

	return createResult(expressionInfo);
}