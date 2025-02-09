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

		PRINT,

		LPAREN,
		RPAREN,

		END_OF_FILE
	};
}

#endif // _TOKENTYPE_H_