#include "parser/parser.h"
#include "parser/expression/letExpression.h"

using namespace lotus;

Expression lotus::Parser::handleLetExpression() {
	String name = consume(TokenType::WORD).text;

	Expression value = nullptr;
	if (match(TokenType::EQUAL)) {
		value = expression();
	}

	return MAKE_PTR<LetExpression>(name, value, module.variables);
}