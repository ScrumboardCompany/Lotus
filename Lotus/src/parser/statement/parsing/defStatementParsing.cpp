#include "parser/parser.h"
#include "parser/statement/defStatement.h"

using namespace lotus;

Statement lotus::Parser::handleDefStatement() {
	String name = consume(TokenType::WORD).text;

	consume(TokenType::LPAREN);

	consume(TokenType::RPAREN);

	Statement body = handleBlockStatement();

	return MAKE_PTR<DefStatement>(name, functions, body);
}