#include "parser/parser.h"
#include "parser/expression/unaryExpression.h"

using namespace lotus;

Expression lotus::Parser::unary() {

	if (match(TokenType::PLUS)) {
		return MAKE_PTR<UnaryExpression>(primary(), UnaryOperationType::PLUS);
	}
	if (match(TokenType::MINUS)) {
		return MAKE_PTR<UnaryExpression>(primary(), UnaryOperationType::MINUS);
	}

	return primary();
}