#pragma once

#ifndef _FUNCTION_
#define _FUNCTION_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Function {
		Statement body;

	public:
		Function(const Statement& body);
		Function() = default;
		~Function() = default;
		Value call();
	};

}

#endif // _FUNCTION_