#include "parser/parser.h"
#include "parser/expression/arithmeticExpression.h"

using namespace lotus;

Expression lotus::Parser::additive() {
	Expression result = multiplicative();
	while (true) {
		if (match(TokenType::PLUS)) {
			result = MAKE_PTR<ArithmeticExpression>(result, multiplicative(), ArithmeticOperationType::ADD);
			continue;
		}
		else if (match(TokenType::MINUS)) {
			result = MAKE_PTR<ArithmeticExpression>(result, multiplicative(), ArithmeticOperationType::SUBSTRACT);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::multiplicative() {
	Expression result = unary();
	while (true) {
		if (match(TokenType::STAR)) {
			result = MAKE_PTR<ArithmeticExpression>(result, unary(), ArithmeticOperationType::MULTIPLY);
			continue;
		}
		else if (match(TokenType::SLASH)) {
			result = MAKE_PTR<ArithmeticExpression>(result, unary(), ArithmeticOperationType::DIVIDE);
			continue;
		}
		break;
	}
	return result;
}