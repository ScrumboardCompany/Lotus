#include "parser/parser.h"

using namespace lotus;

std::vector<Expression> lotus::Parser::handleCommas() {
	std::vector<Expression> expressions;

	while (true) {
		expressions.push_back(expression());

		if (!match(TokenType::COMMA)) {
			break;
		}
	}

	return expressions;
}