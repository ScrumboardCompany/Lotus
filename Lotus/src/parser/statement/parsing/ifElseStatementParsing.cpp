#include "parser/parser.h"
#include "parser/statement/ifElseStatement.h"

using namespace lotus;

Statement lotus::Parser::handleIfElseStatement() {
	consume(TokenType::LPAREN);

	Expression condition = expression();

	consume(TokenType::RPAREN);

	Statement ifBody = handleBlockStatement();

	Statement elseBody;

	if (match(TokenType::ELSE)) {
		elseBody = handleBlockStatement();
	}

	return MAKE_PTR<IfElseStatement>(condition, ifBody, elseBody);
}