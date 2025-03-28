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
			{STRING_LITERAL("<="), TokenType::LESSEQUAL},
			{STRING_LITERAL("=="), TokenType::EQUALEQUAL},
			{STRING_LITERAL("!="), TokenType::NOTEQUAL},
			{STRING_LITERAL("||"), TokenType::BARBAR},
			{STRING_LITERAL("&&"), TokenType::AMPAMP},
			{STRING_LITERAL("!"), TokenType::NOT},
			{STRING_LITERAL("("), TokenType::LPAREN},
			{STRING_LITERAL(")"), TokenType::RPAREN},
			{STRING_LITERAL("{"), TokenType::LBRACE},
			{STRING_LITERAL("}"), TokenType::RBRACE},
			{STRING_LITERAL("["), TokenType::LBRACKET},
			{STRING_LITERAL("]"), TokenType::RBRACKET},
			{STRING_LITERAL(";"), TokenType::SEMICOLON},
			{STRING_LITERAL(":"), TokenType::COLON},
			{STRING_LITERAL(","), TokenType::COMMA},
			{STRING_LITERAL("<<"), TokenType::LESSLESS},
			{STRING_LITERAL(">>"), TokenType::GREATERGREATER},
			{STRING_LITERAL("<<<"), TokenType::LESSLESSLESS},
			{STRING_LITERAL("+="), TokenType::PLUSEQUAL},
			{STRING_LITERAL("-="), TokenType::MINUSEQUAL},
			{STRING_LITERAL("*="), TokenType::STARQUAL},
			{STRING_LITERAL("/="), TokenType::SLASHQUAL},
			{STRING_LITERAL("**="), TokenType::STARSTAREQUAL},
			{STRING_LITERAL("//="), TokenType::SLASHSLASHEQUAL},
			{STRING_LITERAL(">>="), TokenType::GREATERGREATEREQUAL},
			{STRING_LITERAL("<<="), TokenType::LESSLESSEQUAL},
			{STRING_LITERAL("&="), TokenType::AMPEQUAL},
			{STRING_LITERAL("|="), TokenType::BAREQUAL},
			{STRING_LITERAL("^="), TokenType::CARETEQUAL},
			{STRING_LITERAL("~="), TokenType::TILDAEQUAL},
			{STRING_LITERAL("++"), TokenType::PLUSPLUS},
			{STRING_LITERAL("--"), TokenType::MINUSMINUS},
			{STRING_LITERAL("**"), TokenType::STARSTAR},
			{STRING_LITERAL("//"), TokenType::SLASHSLASH},
			{STRING_LITERAL("&"), TokenType::AMP},
			{STRING_LITERAL("|"), TokenType::BAR},
			{STRING_LITERAL("~"), TokenType::TILDA},
			{STRING_LITERAL("^"), TokenType::CARET},
			{STRING_LITERAL("."), TokenType::DOT},
			{STRING_LITERAL("?"), TokenType::QUESTION},
			{STRING_LITERAL("::"), TokenType::COLONCOLON},
			{STRING_LITERAL("..."), TokenType::DOTDOTDOT},
			{STRING_LITERAL("=>"), TokenType::EQUALGREATER},
		};

		StringMap<TokenType> keywords = {
			{STRING_LITERAL("let"), TokenType::LET},
			{STRING_LITERAL("if"), TokenType::IF},
			{STRING_LITERAL("else"), TokenType::ELSE},
			{STRING_LITERAL("while"), TokenType::WHILE},
			{STRING_LITERAL("undefined"), TokenType::UNDEFINED_},
			{STRING_LITERAL("true"), TokenType::TRUE},
			{STRING_LITERAL("false"), TokenType::FALSE},
			{STRING_LITERAL("for"), TokenType::FOR},
			{STRING_LITERAL("foreach"), TokenType::FOREACH},
			{STRING_LITERAL("flag"), TokenType::FLAG},
			{STRING_LITERAL("continue"), TokenType::CONTINUE},
			{STRING_LITERAL("break"), TokenType::BREAK},
			{STRING_LITERAL("return"), TokenType::RETURN},
			{STRING_LITERAL("def"), TokenType::DEF},
			{STRING_LITERAL("class"), TokenType::CLASS},
			{STRING_LITERAL("switch"), TokenType::SWITCH},
			{STRING_LITERAL("case"), TokenType::CASE},
			{STRING_LITERAL("default"), TokenType::DEFAULT},
			{STRING_LITERAL("public"), TokenType::PUBLIC},
			{STRING_LITERAL("private"), TokenType::PRIVATE},
			{STRING_LITERAL("protected"), TokenType::PROTECTED},
			{STRING_LITERAL("static"), TokenType::STATIC},
			{STRING_LITERAL("try"), TokenType::TRY},
			{STRING_LITERAL("catch"), TokenType::CATCH},
			{STRING_LITERAL("flagValue"), TokenType::FLAGVALUE},
			{STRING_LITERAL("variable"), TokenType::VARIABLE},
			{STRING_LITERAL("function"), TokenType::FUNCTION},
			{STRING_LITERAL("enum"), TokenType::ENUM},
			{STRING_LITERAL("swap"), TokenType::SWAP},
			{STRING_LITERAL("__file__"), TokenType::___FILE___},
			{STRING_LITERAL("__path__"), TokenType::___PATH___},
			{STRING_LITERAL("__time__"), TokenType::___TIME___},
			{STRING_LITERAL("__version__"), TokenType::___VERSION___},
			{STRING_LITERAL("__line__"), TokenType::___LINE___}
		};

		String input;
		std::list<Token> tokens;
		size_t pos;
		size_t line;

	public:

		Lexer(const String& input);

		std::list<Token> tokenize();

	private:

		void tokenizeNumber();

		void tokenizeWord();

		void tokenizeText();

		void tokenizeOperator();

		void tokenizeComment();

		void tokenizeMultiComment();

		void tokenizeHex();

		Char peek(size_t relativePosition) const;

		Char next();

		void addToken(const TokenType& type, const String& text);

		bool isStartOperator(Char ch);

		bool isWordChar(Char ch, bool checkNumber = true);
	};
}

#endif // _LEXER_