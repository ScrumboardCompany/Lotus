#include "parser/parser.h"
#include "parser/statement/forEachStatement.h"

using namespace lotus;

Statement lotus::Parser::handleForEachStatement() {
	consume(TokenType::LPAREN);

	String name = consume(TokenType::WORD).text;

	consume(TokenType::COLON);

	Expression expr = expression();

	consume(TokenType::RPAREN);

	Statement body = handleBlockStatement();

	return MAKE_PTR<ForEachStatement>(expr, name, module.variables, body);
}