#pragma once

#ifndef _TOKEN_
#define _TOKEN_

#include "tokenType.h"
#include "utils/lotusTypes.h"

namespace lotus {

	struct Token {
		TokenType type;
		String text;
		size_t line;

		String type_to_string() const;
	};
}

#endif // _TOKEN_H_