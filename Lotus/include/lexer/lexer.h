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
			{STRING_LITERAL("="), TokenType::EQUAL},
			{STRING_LITERAL(">"), TokenType::GREATER},
			{STRING_LITERAL("<"), TokenType::LESS},
			{STRING_LITERAL(">="), TokenType::GREATEREQUAL},
			{STRING_LITERAL("<"), TokenType::LESSEQUAL},
			{STRING_LITERAL("=="), TokenType::EQUALEQUAL},
			{STRING_LITERAL("!="), TokenType::NOTEQUAL},
			{STRING_LITERAL("||"), TokenType::BARBAR},
			{STRING_LITERAL("&&"), TokenType::AMPAMP},
			{STRING_LITERAL("!"), TokenType::NOT},
			{STRING_LITERAL("("), TokenType::LPAREN},
			{STRING_LITERAL(")"), TokenType::RPAREN},
			{STRING_LITERAL("{"), TokenType::LBRACE},
			{STRING_LITERAL("}"), TokenType::RBRACE},
			{STRING_LITERAL(";"), TokenType::SEMICOLON},
			{STRING_LITERAL(","), TokenType::COMMA},
		};

		StringMap<TokenType> keywords = {
			{STRING_LITERAL("print"), TokenType::PRINT},
			{STRING_LITERAL("let"), TokenType::LET},
			{STRING_LITERAL("if"), TokenType::IF},
			{STRING_LITERAL("else"), TokenType::ELSE},
			{STRING_LITERAL("while"), TokenType::WHILE},
			{STRING_LITERAL("undefined"), TokenType::UNDEFINED_},
			{STRING_LITERAL("true"), TokenType::TRUE},
			{STRING_LITERAL("false"), TokenType::FALSE},
			{STRING_LITERAL("for"), TokenType::FOR}
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

		bool isStartOperator(Char ch);

		bool isWordChar(Char ch, bool checkNumber = true);
	};
}

#endif // _LEXER_