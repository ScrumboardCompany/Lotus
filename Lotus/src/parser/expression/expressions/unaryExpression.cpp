#include "parser/expression/unaryExpression.h"

using namespace lotus;

lotus::UnaryExpression::UnaryExpression(const Expression& expression, const UnaryOperationType& operation)
	: expression(expression), operation(operation) {}

Value lotus::UnaryExpression::eval() {
	Value result;

	switch (operation) {
	case lotus::UnaryOperationType::PLUS:
		result = expression->eval()->unaryPlus();
		break;
	case lotus::UnaryOperationType::MINUS:
		result = expression->eval()->unaryMinus();
		break;
	case lotus::UnaryOperationType::NOT:
		result = expression->eval()->unaryNot();
	default:
		break;
	}

	return result;
}
