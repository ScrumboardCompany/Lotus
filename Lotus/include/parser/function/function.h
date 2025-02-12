#pragma once

#ifndef _FUNCTION_
#define _FUNCTION_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"
#include "structures/variables.h"

namespace lotus {

	class Function {
		Statement body;
		Variables* variables;

	public:
		Function(const Statement& body, Variables* variables);
		Function() = default;
		~Function() = default;
		Value call();
	};

}

#endif // _FUNCTION_