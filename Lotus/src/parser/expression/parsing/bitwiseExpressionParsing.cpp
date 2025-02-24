#include "parser/parser.h"
#include "parser/expression/bitwiseExpression.h"

using namespace lotus;

Expression lotus::Parser::bitwise() {
	Expression result = bitwiseShifts();

	while (true) {
		if (match(TokenType::AMP)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseShifts(), BitwiseOperationType::AND);
			continue;
		}
		if (match(TokenType::BAR)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseShifts(), BitwiseOperationType::OR);
			continue;
		}
		if (match(TokenType::CARET)) {
			result = MAKE_PTR<BitwiseExpression>(result, bitwiseShifts(), BitwiseOperationType::XOR);
			continue;
		}
		break;
	}
	return result;
}

Expression Parser::bitwiseShifts() {
	Expression result = additive();

	while (true) {
		if (match(TokenType::LESSLESS)) {
			result = MAKE_PTR<BitwiseExpression>(result, additive(), BitwiseOperationType::LEFTSHIFT);
			continue;
		}
		if (match(TokenType::GREATERGREATER)) {
			result = MAKE_PTR<BitwiseExpression>(result, additive(), BitwiseOperationType::RIGHTSHIFT);
			continue;
		}
		break;
	}
	return result;
}