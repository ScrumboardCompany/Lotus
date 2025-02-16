#include "parser/parser.h"
#include "parser/statement/forStatement.h"

using namespace lotus;

Statement lotus::Parser::handleForStatement() {
	consume(TokenType::LPAREN);

	std::vector<Expression> declaringPart;
	if (!match(TokenType::SEMICOLON)) {
		declaringPart = handleExpressions();

		consume(TokenType::SEMICOLON);
	}

	std::vector<Expression> conditionPart;
	if (!match(TokenType::SEMICOLON)) {
		conditionPart = handleExpressions();

		consume(TokenType::SEMICOLON);
	}

	std::vector<Expression> actionPart;
	if (!match(TokenType::RPAREN)) {
		actionPart = handleExpressions();
		consume(TokenType::RPAREN);
	}

	Statement body = handleBlockStatement();

	return MAKE_PTR<ForStatement>(declaringPart, conditionPart, actionPart, body, module.variables);
}