#pragma once

#ifndef _PARSER_
#define _PARSER_

#include <vector>
#include "utils/lotusTypes.h"
#include "lexer/token.h"
#include "utils/lotusDefines.h"
#include "structures/variables.h"
#include "structures/functions.h"
#include "structures/flags.h"
#include "structures/module.h"

#define EOF_TOKEN lotus::Token({ lotus::TokenType::END_OF_FILE, STRING_LITERAL("")})

namespace lotus {

	class Parser {
		std::vector<Token> tokens;
		size_t pos;

		Module module;

		StringMap<Module> modules;

		Flags flags;

		friend class ImportStatement;

	public:
		Parser(const std::list<Token>& tokens);

		std::vector<Statement> parse();

		Module getModule() const;

	private:

		Statement getNextStatement();

		Statement handlePrintStatement();

		Expression handleLetExpression();

		Statement handleIfElseStatement();

		Statement handleWhileStatement();
		
		Statement handleForStatement();

		Statement handleForEachStatement();

		Statement handleImportStatement();

		Statement handleFlagStatement();

		Statement handleContinueStatement();

		Statement handleBreakStatement();

		Statement handleBlockStatement();

		Statement handleReturnStatement();

		Statement handleDefStatement();

		std::vector<Expression> handleCommas();

		Expression expression();

		Expression logicalOr();

		Expression logicalAnd();

		Expression equality();

		Expression conditional();

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