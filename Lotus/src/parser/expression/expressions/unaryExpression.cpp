#include "parser/expression/unaryExpression.h"
#include "utils/lotusError.h"

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
		break;
	case lotus::UnaryOperationType::PREFIXINCREMENT:
		result = expression->eval()->prefixIncrement();
		break;
	case lotus::UnaryOperationType::POSTFIXINCREMENT:
		result = expression->eval()->postfixIncrement();
		break;
	case lotus::UnaryOperationType::PREFIXDECREMENT:
		result = expression->eval()->prefixDecrement();
		break;
	case lotus::UnaryOperationType::POSTFIXDECREMENT:
		result = expression->eval()->postfixDecrement();
		break;
	default:
		throw LotusException(STRING_LITERAL("Undefined unary operation"));
	}

	return result;
}
