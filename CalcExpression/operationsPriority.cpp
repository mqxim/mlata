#include "operationsPriority.hpp"
#include <map>
#include <set>

typedef std::map<Operation, int> OperationsPriority;
typedef std::set<Operation> AllowedOperations;

static OperationsPriority PRIORITY = {
	std::make_pair(ADDITION, 2),
	std::make_pair(MULTIPLICATION, 1),
	std::make_pair(SUBTRACTION, 2),
	std::make_pair(DIVISION, 1),
	std::make_pair(EXPONENTIATION, 0),
	std::make_pair(EMPTY_OPERATION, -1)
};

static AllowedOperations ALLOWED_OPERATIONS = {
	ADDITION,
	MULTIPLICATION,
	DIVISION,
	EXPONENTIATION,
	SUBTRACTION
};

bool isOperation(Operation operation)
{
    return (ALLOWED_OPERATIONS.find(operation) != ALLOWED_OPERATIONS.end());
}

bool hasMorePriority(Operation first, Operation second)
{
    return (PRIORITY[first] >= PRIORITY[second]);
}