#include "parser/parser.h"
#include "parser/statement/blockStatement.h"

using namespace lotus;

Statement lotus::Parser::handleBlockStatement() {
	std::vector<Statement> statements;

	if (match(TokenType::LBRACE)) {
		while (!match(TokenType::RBRACE)) {
			statements.push_back(getNextStatement());
		}
	}
	else {
		statements.push_back(getNextStatement());
	}

	return MAKE_PTR<BlockStatement>(statements);
}