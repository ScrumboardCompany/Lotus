#include "parser/parser.h"
#include "parser/statement/whileStatement.h"

using namespace lotus;

Statement lotus::Parser::handleWhileStatement() {
	consume(TokenType::LPAREN);

	Expression condition = expression();

	consume(TokenType::RPAREN);

	Statement body = handleBlockStatement();

	return MAKE_PTR<WhileStatement>(condition, body);
}