#include "removeExtraBrackets.hpp"
#include "constants.hpp"

const int MIN_LENGTH = 2;

bool isExpressionValid(std::string expression)
{
    bool isLongEnough = expression.length() >= MIN_LENGTH;
    if (!isLongEnough)
    {
        return false;
    }

    bool opensWithLeft = expression[0] == LEFT_BRACKET;
    bool opensWithRight = expression[expression.length() - 1] == RIGHT_BRACKET;
    return opensWithLeft && opensWithRight;
}

bool couldBracketsBeRemoved(std::string expression, int quantity)
{
    const int length = expression.length();

    if (quantity > length)
    {
        return false;
    }

    bool status = true;
    for (int i = 0; i < quantity; i++)
    {
        status = (expression[i] == LEFT_BRACKET) && (expression[length - i - 1] == RIGHT_BRACKET);
        if (!status)
        {
            return false;
        }
    }
    return true;
}

bool doesNeedBrackets(std::string expression)
{
    int counter = 0;
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == LEFT_BRACKET)
        {
            counter++;
        }

        if (expression[i] == RIGHT_BRACKET)
        {
            counter--;
        }

        if (counter < 0)
        {
            return true;
        }
    }

    return (counter != 0);
}

std::string removeBrackets(std::string expression, int quantity)
{
    int length = expression.length();
    bool isOk = (quantity < length);
    if (!isOk)
    {
        return "";
    }

	std::string result;
    for (int i = quantity ; i < (length - quantity); i++)
    {
        result = result + expression[i];
    }
    return result;
}

std::string addMissingBrackets(std::string expression)
{
	std::string result = expression;

    while (doesNeedBrackets(expression))
    {
        expression = LEFT_BRACKET + expression + RIGHT_BRACKET;
    }
    return expression;
}

std::string removeExtraBrackets(std::string expression)
{
    if (!isExpressionValid(expression))
    {
        return expression;
    }

    int counter = 0;
    int leftBrackets = 0;

    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == LEFT_BRACKET)
        {
            counter++;
            leftBrackets = 0;
        }
        else
        if (expression[i] == RIGHT_BRACKET)
        {
            counter--;
            leftBrackets++;
        }

        if (counter < 0)
        {
            return "";
        }
    }

    if (counter > 0)
    {
        return "";
    }

	std::string result = expression;
    if ((counter == 0) && (leftBrackets > 0))
    {
        for (int i = leftBrackets; i > 0; i--)
        {
            if (couldBracketsBeRemoved(expression, i))
            {
                leftBrackets = i;
                break;
            }
        }

        if (leftBrackets == 0)
        {
            return result;
        }

        result = removeBrackets(expression, leftBrackets);
        result = addMissingBrackets(result);
    }
    return result;
}