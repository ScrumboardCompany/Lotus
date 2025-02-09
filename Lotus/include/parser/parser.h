#pragma once

#ifndef _PARSER_
#define _PARSER_

#include <vector>
#include "utils/lotusTypes.h"
#include "lexer/token.h"
#include "utils/lotusDefines.h"

#define EOF_TOKEN lotus::Token({ lotus::TokenType::END_OF_FILE, STRING_LITERAL("")})

namespace lotus {

	class Parser {
		std::vector<Token> tokens;
		size_t pos;

	public:
		Parser(const std::list<Token>& tokens);

		std::vector<Statement> parse();

	private:

		Statement getNextStatement();

		Statement handlePrintStatement();

		Expression expression();

		Expression additive();

		Expression multiplicative();

		Expression unary();

		Expression primary();

		Token get(const size_t relativePosition);

		bool match(const TokenType type);

		Token consume(const TokenType type);
	};
}

#endif // _PARSER_