#include "parser/parser.h"
#include "parser/expression/bitwiseExpression.h"

using namespace lotus;

Expression lotus::Parser::bitwise() {
	Expression result = bitwiseShifts();

	while (true) {
		if (match(TokenType::AMP)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseShifts(), BitwiseOperationType::AND, module.variables);
			continue;
		}
		if (match(TokenType::BAR)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseShifts(), BitwiseOperationType::OR, module.variables);
			continue;
		}
		if (match(TokenType::CARET)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseShifts(), BitwiseOperationType::XOR, module.variables);
			continue;
		}
		break;
	}
	return result;
}

Expression Parser::bitwiseShifts() {
	Expression result = bitwiseNot();

	while (true) {
		if (match(TokenType::LESSLESS)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseNot(), BitwiseOperationType::LEFTSHIFT, module.variables);
			continue;
		}
		if (match(TokenType::GREATERGREATER)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseNot(), BitwiseOperationType::RIGHTSHIFT, module.variables);
			continue;
		}
		break;
	}
	return result;
}

Expression Parser::bitwiseNot() {

	std::vector<BitwiseOperationType> operations;

	while (true) {
		if (match(TokenType::TILDA)) {
			operations.push_back(BitwiseOperationType::NOT);
		}
		else {
			break;
		}
	}

	Expression result = additive();

	for (auto it = operations.rbegin(); it != operations.rend(); ++it) {
		result = MAKE_PTR<BitwiseExpression>(result, nullptr, *it, module.variables);
	}

	return result;
}