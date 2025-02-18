#include "parser/expression/bitwiseExpression.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::BitwiseExpression::BitwiseExpression(const Expression& expression1, const Expression& expression2, const BitwiseOperationType& operation)
	: expression1(expression1), expression2(expression2), operation(operation) {
}

Value lotus::BitwiseExpression::eval() {
	Value value1 = expression1->eval();
	Value value2 = expression2 ? expression2->eval() : UNDEFINED();

	Value result;

	switch (operation) {
	case lotus::BitwiseOperationType::AND:
		result = value1->bitwiseAnd(value2);
		break;
	case lotus::BitwiseOperationType::OR:
		result = value1->bitwiseOr(value2);
		break;
	case lotus::BitwiseOperationType::XOR:
		result = value1->bitwiseXor(value2);
		break;
	case lotus::BitwiseOperationType::NOT:
		result = value1->bitwiseNot();
		break;
	case lotus::BitwiseOperationType::LEFTSHIFT:
		result = value1->bitwiseLeftShift(value2);
		break;
	case lotus::BitwiseOperationType::RIGHTSHIFT:
		result = value1->bitwiseRightShift(value2);
		break;
	default:
		throw LotusException(STRING_LITERAL("Undefined bitwise operation"));
	}

	return result;
}