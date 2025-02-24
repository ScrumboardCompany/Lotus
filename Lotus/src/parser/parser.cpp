#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"
#include "parser/statement/expressionStatement.h"
#include "parser/value/floatValue.h"
#include "parser/statement/cppFunctionStatement.h"
#include <iostream>

#include <cmath>

using namespace lotus;

lotus::Parser::Parser(const std::list<Token>& tokens) : pos(0) {
	this->tokens.clear();
	for (auto& token : tokens) {
		this->tokens.push_back(token);
	}

	loadModules();
}

std::vector<Statement> lotus::Parser::parse() {
	std::vector<Statement> statements;
	while (!match(TokenType::END_OF_FILE)) {
		statements.push_back(getNextGlobalStatement());
	}
	return statements;
}

Module& lotus::Parser::getModule() {
	return module;
}

Statement lotus::Parser::getNextGlobalStatement() {
	Statement statement;

	if (match(TokenType::FLAG)) {
		statement = handleFlagStatement();
	} 
	else if (match(TokenType::DEF)) {
		statement = handleDefStatement();
	}
	else if (match(TokenType::CLASS)) { 
		statement = handleClassStatement();
	}
	else if (match(TokenType::STATIC)) {
		statement = handleStaticStatement();
	}
	else if ((get(0).type == TokenType::WORD || get(0).type == TokenType::STAR) && get(1).type == TokenType::LESSLESSLESS) {
		statement = handleImportStatement();
	}
	else statement = getNextStatement();

	while (match(TokenType::SEMICOLON));

	return statement;
}

Statement lotus::Parser::getNextStatement() {
	Statement statement;

	if (match(TokenType::IF)) {
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
	else if (match(TokenType::CONTINUE)) {
		statement = handleContinueStatement();
	}
	else if (match(TokenType::BREAK)) {
		statement = handleBreakStatement();
	}
	else if (match(TokenType::RETURN)) {
		statement = handleReturnStatement();
	}
	else if (match(TokenType::SWITCH)) {
		statement = handleSwitchCaseStatement();
	}
	else statement = MAKE_PTR<ExpressionStatement>(expression());

	while (match(TokenType::SEMICOLON));

	return statement;
}