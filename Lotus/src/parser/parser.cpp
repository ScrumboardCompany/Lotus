#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"

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
	if (match(TokenType::PRINT)) {
		return handlePrintStatement();
	}
	else if (match(TokenType::LET)) {
		return handleLetStatement();
	}
	else if (get(0).type == TokenType::WORD && get(1).type == TokenType::EQUAL) {
		return handleSetStatement();
	}
	
	throw LotusException("Undefined statement");
}