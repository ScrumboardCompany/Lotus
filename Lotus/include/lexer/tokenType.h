#pragma once

#ifndef _TOKENTYPE_H_
#define _TOKENTYPE_H_

namespace lotus {

	enum class TokenType {
		INT_TYPE,
		FLOAT_TYPE,
		WORD,
		TEXT,

		PLUS,
		MINUS,
		STAR,
		SLASH,

		LPAREN,
		RPAREN,

		END_OF_FILE
	};
}

#endif // _TOKENTYPE_H_