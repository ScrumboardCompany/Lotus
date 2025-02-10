#include "parser/parser.h"
#include "parser/expression/logicalExpression.h"

using namespace lotus;

Expression lotus::Parser::logicalOr() {
	Expression result = logicalAnd();

	while (true) {
		if (match(TokenType::BARBAR)) {
			result = MAKE_PTR<LogicalExpression>(result, logicalAnd(), LogicalOperationType::OR);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::logicalAnd() {
	Expression result = equality();

	while (true) {
		if (match(TokenType::AMPAMP)) {
			result = MAKE_PTR<LogicalExpression>(result, equality(), LogicalOperationType::AND);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::equality() {
	Expression result = conditional();

	while (true) {
		if (match(TokenType::EQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, conditional(), LogicalOperationType::EQUALITY);
			continue;
		}
		if (match(TokenType::NOTEQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, conditional(), LogicalOperationType::INEQUALITY);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::conditional() {
	Expression result = additive();

	while (true) {
		if (match(TokenType::LESS)) {
			result = MAKE_PTR<LogicalExpression>(result, additive(), LogicalOperationType::LESS);
			continue;
		}
		if (match(TokenType::LESSEQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, additive(), LogicalOperationType::LESSEQUAL);
			continue;
		}
		if (match(TokenType::GREATER)) {
			result = MAKE_PTR<LogicalExpression>(result, additive(), LogicalOperationType::GREATER);
			continue;
		}
		if (match(TokenType::GREATEREQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, additive(), LogicalOperationType::GREATEREQUAL);
			continue;
		}
		break;
	}
	return result;
}