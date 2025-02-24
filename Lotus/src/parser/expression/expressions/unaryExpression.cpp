#include "parser/expression/unaryExpression.h"
#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::UnaryExpression::UnaryExpression(const Expression& expression, const UnaryOperationType& operation)
	: expression(expression), operation(operation) {}

Value lotus::UnaryExpression::eval(Module& module) {
	Value result;

	switch (operation) {
	case lotus::UnaryOperationType::PLUS:
		result = expression->eval(module)->unaryPlus(module);
		break;
	case lotus::UnaryOperationType::MINUS:
		result = expression->eval(module)->unaryMinus(module);
		break;
	case lotus::UnaryOperationType::LOGICALNOT:
		result = expression->eval(module)->unaryNot(module);
		break;
	case lotus::UnaryOperationType::BITWISENOT:
		result = expression->eval(module)->bitwiseNot(module);
		break;
	case lotus::UnaryOperationType::PREFIXINCREMENT:
		result = expression->eval(module)->prefixIncrement(module);
		break;
	case lotus::UnaryOperationType::POSTFIXINCREMENT:
		result = expression->eval(module)->postfixIncrement(module);
		break;
	case lotus::UnaryOperationType::PREFIXDECREMENT:
		result = expression->eval(module)->prefixDecrement(module);
		break;
	case lotus::UnaryOperationType::POSTFIXDECREMENT:
		result = expression->eval(module)->postfixDecrement(module);
		break;
	default:
		throw LotusException(STRING_LITERAL("Undefined unary operation"));
	}

	return result;
}

