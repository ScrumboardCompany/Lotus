#pragma once

#ifndef _TOKENTYPE_H_
#define _TOKENTYPE_H_

namespace lotus {

	enum class TokenType {
		INT_TYPE,
		FLOAT_TYPE,
		STRING_TYPE,
		WORD,

		PLUS,
		MINUS,
		STAR,
		SLASH,
		EQUAL,
		GREATER,
		LESS,
		GREATEREQUAL,
		LESSEQUAL,
		EQUALEQUAL,
		NOTEQUAL,
		BARBAR,
		AMPAMP,
		NOT,
		COMMA,
		LESSLESS,
		GREATERGREATER,
		LESSLESSLESS,

		PRINT,
		LET,
		IF,
		ELSE,
		WHILE,
		UNDEFINED_,
		TRUE,
		FALSE,
		FOR,
		FOREACH,
		FLAG,
		CONTINUE,
		BREAK,
		RETURN,
		DEF,

		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,
		LBRACKET,
		RBRACKET,
		SEMICOLON,
		COLON,

		END_OF_FILE
	};
}

#endif // _TOKENTYPE_H_