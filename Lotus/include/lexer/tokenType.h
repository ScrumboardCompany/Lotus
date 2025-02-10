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

		PRINT,
		LET,
		IF,
		ELSE,
		WHILE,
		UNDEFINED_,
		TRUE,
		FALSE,

		LPAREN,
		RPAREN,
		LBRACE,
		RBRACE,
		SEMICOLON,

		END_OF_FILE
	};
}

#endif // _TOKENTYPE_H_