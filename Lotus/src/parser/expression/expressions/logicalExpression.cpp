#include "parser/expression/logicalExpression.h"

using namespace lotus;

lotus::LogicalExpression::LogicalExpression(const Expression& expression1, const Expression& expression2, const LogicalOperationType& operation)
	: expression1(expression1), expression2(expression2), operation(operation) {
}

Value lotus::LogicalExpression::eval() {
	Value value1 = expression1->eval();
	Value value2 = expression2->eval();

	Value result;

	switch (operation)
	{
	case lotus::LogicalOperationType::GREATER:
		result = value1->greater(value2);
		break;
	case lotus::LogicalOperationType::LESS:
		result = value1->less(value2);
		break;
	case lotus::LogicalOperationType::GREATEREQUAL:
		result = value1->greaterEqual(value2);
		break;
	case lotus::LogicalOperationType::LESSEQUAL:
		result = value1->lessEqual(value2);
		break;
	case lotus::LogicalOperationType::EQUALITY:
		result = value1->equality(value2);
		break;
	case lotus::LogicalOperationType::INEQUALITY:
		result = value1->inequality(value2);
		break;
	case lotus::LogicalOperationType::OR:
		result = value1->logicalOr(value2);
		break;
	case lotus::LogicalOperationType::AND:
		result = value1->logicalAnd(value2);
	default:
		break;
	}

	return result;
}