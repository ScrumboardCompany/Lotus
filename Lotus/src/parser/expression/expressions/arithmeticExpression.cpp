#include "parser/expression/arithmeticExpression.h"

using namespace lotus;

lotus::ArithmeticExpression::ArithmeticExpression(const Expression& expression1, const Expression& expression2, const ArithmeticOperationType& operation)
	: expression1(expression1), expression2(expression2), operation(operation) {}

Value lotus::ArithmeticExpression::eval() {
	Value value1 = expression1->eval();
	Value value2 = expression2->eval();

	Value result;

	switch (operation) {
	case lotus::ArithmeticOperationType::ADD:
		result = value1->add(value2);
		break;
	case lotus::ArithmeticOperationType::SUBSTRACT:
		result = value1->substract(value2);
		break;
	case lotus::ArithmeticOperationType::MULTIPLY:
		result = value1->multiply(value2);
		break;
	case lotus::ArithmeticOperationType::DIVIDE:
		result = value1->divide(value2);
	default:
		break;
	}

	return result;
}