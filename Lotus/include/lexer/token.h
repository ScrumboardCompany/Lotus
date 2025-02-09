#pragma once

#ifndef _TOKEN_
#define _TOKEN_

#include "tokenType.h"
#include "utils/lotusTypes.h"

namespace lotus {

	struct Token {
		TokenType type;
		String text;

		std::string to_string() const;
	};
}

#endif // _TOKEN_H_