#include "parser/parser.h"
#include "parser/statement/setStatement.h"

using namespace lotus;

Statement lotus::Parser::handleSetStatement() {
	String name = consume(TokenType::WORD).text;

	consume(TokenType::EQUAL);

	Expression value = expression();

	return MAKE_PTR<SetStatement>(name, value, variables);
}