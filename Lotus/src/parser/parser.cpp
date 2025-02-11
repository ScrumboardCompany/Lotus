#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"
#include "parser/statement/expressionStatement.h"

using namespace lotus;

lotus::Parser::Parser(const std::list<Token>& tokens) : pos(0) {
	this->tokens.clear();
	for (auto& token : tokens) {
		this->tokens.push_back(token);
	}
}

std::vector<Statement> lotus::Parser::parse() {
	std::vector<Statement> statements;
	while (!match(TokenType::END_OF_FILE)) {
		statements.push_back(getNextStatement());
	}
	return statements;
}

Statement lotus::Parser::getNextStatement() {
	Statement statement;

	if (match(TokenType::PRINT)) {
		statement = handlePrintStatement();
	}
	else if (match(TokenType::IF)) {
		statement = handleIfElseStatement();
	}
	else if (match(TokenType::ELSE)) {
		throw LotusException(STRING_LITERAL("Cannot use else without if"));
	}
	else if (match(TokenType::WHILE)) {
		statement = handleWhileStatement();
	}
	else if (match(TokenType::FOR)) {
		statement = handleForStatement();
	}
	else if (match(TokenType::FOREACH)) {
		statement = handleForEachStatement();
	}
	else if (match(TokenType::FLAG)) {
		statement = handleFlagStatement();
	}
	else if (match(TokenType::CONTINUE)) {
		statement = handleContinueStatement();
	}
	else if (match(TokenType::BREAK)) {
		statement = handleBreakStatement();
	}
	else if ((get(0).type == TokenType::WORD || get(0).type == TokenType::STAR) && get(1).type == TokenType::LESSLESSLESS) {
		statement = handleImportStatement();
	}
	else statement = MAKE_PTR<ExpressionStatement>(expression());

	while (match(TokenType::SEMICOLON));

	return statement;
}