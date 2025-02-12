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
		std::vector<String> args;

	public:
		Function(const Statement& body, Variables* variables, const std::vector<String>& args);
		Function() = default;
		~Function() = default;
		Value call(const std::vector<Value>& args);
	};

}

#endif // _FUNCTION_