#include "parser/parser.h"
#include "parser/statement/switchCaseStatement.h"

using namespace lotus;

Statement lotus::Parser::handleSwitchCaseStatement() {
	consume(TokenType::LPAREN);

	Expression exprToCheck = expression();

	consume(TokenType::RPAREN);

	consume(TokenType::LBRACE);

	std::vector<std::pair<Expression, Statement>> cases;
	Statement defaultBody = nullptr;

	while (!match(TokenType::RBRACE)) {
		if (match(TokenType::CASE)) {
			Expression expr = expression();
			Statement body = handleBlockStatement();

			cases.emplace_back(expr, body);
		}

		if (!defaultBody && match(TokenType::DEFAULT)) {
			defaultBody = handleBlockStatement();
		}
	}

	return MAKE_PTR<SwitchCaseStatement>(exprToCheck, cases, defaultBody, module.variables);
}