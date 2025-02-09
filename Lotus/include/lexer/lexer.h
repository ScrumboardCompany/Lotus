#pragma once

#ifndef _LEXER_
#define _LEXER_

#include "token.h"
#include "utils/lotusDefines.h"
#include <list>

namespace lotus {

	class Lexer {
		
		StringMap<TokenType> operators = {
			{STRING_LITERAL("+"), TokenType::PLUS},
			{STRING_LITERAL("-"), TokenType::MINUS},
			{STRING_LITERAL("*"), TokenType::STAR},
			{STRING_LITERAL("/"), TokenType::SLASH},
			{STRING_LITERAL("("), TokenType::LPAREN},
			{STRING_LITERAL(")"), TokenType::RPAREN},
		};

		String input;
		std::list<Token> tokens;
		size_t pos;

	public:

		Lexer(const String& input);

		std::list<Token> tokenize();

	private:

		void tokenizeNumber();

		void tokenizeWord();

		void tokenizeText();

		void tokenizeOperator();

		Char peek(const size_t relativePosition) const;

		Char next();

		void addToken(const TokenType& type, const String& text = STRING_LITERAL(""));

		bool isWordChar(Char ch, bool checkNumber = true);
	};
}

#endif // _LEXER_