#pragma once

#ifndef _FLAGCONFIGPARSER_
#define _FLAGCONFIGPARSER_

#include "lexer/token.h"
#include "structures/flags.h"

namespace lotus {

	class FlagConfigParser {
		std::vector<Token> tokens;
		size_t pos;

		Token get(const size_t relativePosition);

		bool match(const TokenType type);

		Token consume(const TokenType type);

		StringMap<bool> flags;

	public:
		FlagConfigParser(const std::list<Token>& tokens);

		void parse();

		StringMap<bool> getFlags() const;
	};
}

#endif // _FLAGCONFIGPARSER_