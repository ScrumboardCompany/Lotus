#include "parser/expression/unaryExpression.h"
#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::UnaryExpression::UnaryExpression(const Expression& expression, const UnaryOperationType& operation, Variables& variables)
	: expression(expression), operation(operation), variables(variables) {}

Value lotus::UnaryExpression::eval() {
	Value result;

	switch (operation) {
	case lotus::UnaryOperationType::PLUS:
		result = expression->eval()->unaryPlus(variables);
		break;
	case lotus::UnaryOperationType::MINUS:
		result = expression->eval()->unaryMinus(variables);
		break;
	case lotus::UnaryOperationType::LOGICALNOT:
		result = expression->eval()->unaryNot(variables);
		break;
	case lotus::UnaryOperationType::BITWISENOT:
		result = expression->eval()->bitwiseNot(variables);
		break;
	case lotus::UnaryOperationType::PREFIXINCREMENT:
		result = expression->eval()->prefixIncrement(variables);
		break;
	case lotus::UnaryOperationType::POSTFIXINCREMENT:
		result = expression->eval()->postfixIncrement(variables);
		break;
	case lotus::UnaryOperationType::PREFIXDECREMENT:
		result = expression->eval()->prefixDecrement(variables);
		break;
	case lotus::UnaryOperationType::POSTFIXDECREMENT:
		result = expression->eval()->postfixDecrement(variables);
		break;
	default:
		throw LotusException(STRING_LITERAL("Undefined unary operation"));
	}

	return result;
}

