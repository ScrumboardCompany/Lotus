#include "parser/parser.h"
#include "parser/statement/ifElseStatement.h"

using namespace lotus;

Statement lotus::Parser::handleIfElseStatement() {
	consume(TokenType::LPAREN);

	std::vector<Expression> conditionPart = handleExpressions();

	consume(TokenType::RPAREN);

	Statement ifBody = handleBlockStatement();

	Statement elseBody;

	if (match(TokenType::ELSE)) {
		elseBody = handleBlockStatement();
	}

	return MAKE_PTR<IfElseStatement>(conditionPart, ifBody, elseBody, module.variables);
}