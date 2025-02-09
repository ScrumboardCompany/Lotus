#include "parser/parser.h"
#include "parser/statement/letStatement.h"

using namespace lotus;

Statement lotus::Parser::handleLetStatement() {
	String name = consume(TokenType::WORD).text;

	Expression value = nullptr;
	if (match(TokenType::EQUAL)) {
		value = expression();
	}

	return MAKE_PTR<LetStatement>(name, value, variables);
}