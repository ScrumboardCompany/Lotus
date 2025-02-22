#include "parser/parser.h"
#include "parser/expression/logicalExpression.h"

using namespace lotus;

Expression lotus::Parser::logicalOr() {
	Expression result = logicalAnd();

	while (true) {
		if (match(TokenType::BARBAR)) {
			result = MAKE_PTR<LogicalExpression>(result, logicalAnd(), LogicalOperationType::OR, module.variables);
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
			result = MAKE_PTR<LogicalExpression>(result, equality(), LogicalOperationType::AND, module.variables);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::equality() {
	Expression result = conditional();

	while (true) {
		if (match(TokenType::EQUALEQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, conditional(), LogicalOperationType::EQUALITY, module.variables);
			continue;
		}
		if (match(TokenType::NOTEQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, conditional(), LogicalOperationType::INEQUALITY, module.variables);
			continue;
		}
		break;
	}
	return result;
}

Expression lotus::Parser::conditional() {
	Expression result = bitwise();

	while (true) {
		if (match(TokenType::LESS)) {
			result = MAKE_PTR<LogicalExpression>(result, bitwise(), LogicalOperationType::LESS, module.variables);
			continue;
		}
		if (match(TokenType::LESSEQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, bitwise(), LogicalOperationType::LESSEQUAL, module.variables);
			continue;
		}
		if (match(TokenType::GREATER)) {
			result = MAKE_PTR<LogicalExpression>(result, bitwise(), LogicalOperationType::GREATER, module.variables);
			continue;
		}
		if (match(TokenType::GREATEREQUAL)) {
			result = MAKE_PTR<LogicalExpression>(result, bitwise(), LogicalOperationType::GREATEREQUAL, module.variables);
			continue;
		}
		break;
	}
	return result;
}