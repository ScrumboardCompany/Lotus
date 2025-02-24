#include "parser/expression/arithmeticExpression.h"
#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::ArithmeticExpression::ArithmeticExpression(const Expression& expression1, const Expression& expression2, const ArithmeticOperationType& operation)
	: expression1(expression1), expression2(expression2), operation(operation) {}

Value lotus::ArithmeticExpression::eval(Module& module) {
	Value value1 = expression1->eval(module);
	Value value2 = expression2->eval(module);

	Value result;

	switch (operation) {
	case lotus::ArithmeticOperationType::ADD:
		result = value1->add(value2, module);
		break;
	case lotus::ArithmeticOperationType::SUBSTRACT:
		result = value1->substract(value2, module);
		break;
	case lotus::ArithmeticOperationType::MULTIPLY:
		result = value1->multiply(value2, module);
		break;
	case lotus::ArithmeticOperationType::DIVIDE:
		result = value1->divide(value2, module);
		break;
	case lotus::ArithmeticOperationType::POWER:
		result = value1->power(value2, module);
		break;
	case lotus::ArithmeticOperationType::MODULE:
		result = value1->divideModule(value2, module);
		break;
	default:
		throw LotusException(STRING_LITERAL("Undefined arithmetic operation"));
	}

	return result;
}