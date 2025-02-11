#include "parser/parser.h"
#include "parser/statement/whileStatement.h"

using namespace lotus;

Statement lotus::Parser::handleWhileStatement() {
	consume(TokenType::LPAREN);

	std::vector<Expression> conditionPart = handleCommas();

	consume(TokenType::RPAREN);

	Statement body = handleBlockStatement();

	return MAKE_PTR<WhileStatement>(conditionPart, body, variables);
}