#include "parser/parser.h"
#include "parser/expression/setExpression.h"

using namespace lotus;

Expression lotus::Parser::handleSetExpression() {
	String name = consume(TokenType::WORD).text;

	consume(TokenType::EQUAL);

	Expression value = expression();

	return MAKE_PTR<SetExpression>(name, value, variables);
}