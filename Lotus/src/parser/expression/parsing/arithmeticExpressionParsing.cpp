#include "parser/parser.h"
#include "parser/expression/arithmeticExpression.h"

using namespace lotus;

Expression lotus::Parser::additive() {
	Expression result = multiplicative();
	while (true) {
		if (match(TokenType::PLUS)) {
			result = MAKE_PTR<ArithmeticExpression>(result, multiplicative(), ArithmeticOperationType::ADD, module.variables);
			continue;
		}
		else if (match(TokenType::MINUS)) {
			result = MAKE_PTR<ArithmeticExpression>(result, multiplicative(), ArithmeticOperationType::SUBSTRACT, module.variables);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::multiplicative() {
	Expression result = exponential();
	while (true) {
		if (match(TokenType::STAR)) {
			result = MAKE_PTR<ArithmeticExpression>(result, exponential(), ArithmeticOperationType::MULTIPLY, module.variables);
			continue;
		}
		else if (match(TokenType::SLASH)) {
			result = MAKE_PTR<ArithmeticExpression>(result, exponential(), ArithmeticOperationType::DIVIDE, module.variables);
			continue;
		} else if (match(TokenType::SLASHSLASH)) {
			result = MAKE_PTR<ArithmeticExpression>(result, exponential(), ArithmeticOperationType::MODULE, module.variables);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::exponential() {
	Expression result = unary();
	while (true) {
		if (match(TokenType::STARSTAR)) {
			result = MAKE_PTR<ArithmeticExpression>(result, unary(), ArithmeticOperationType::POWER, module.variables);
			continue;
		}
		break;
	}
	return result;
}