#pragma once

#ifndef _FUNCTION_
#define _FUNCTION_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"
#include "structures/argument.h"

namespace lotus {

	class LOTUS_API Function {
		Statement body;
		std::vector<Argument> args;

		friend struct Class;

	public:
		Function(const Statement& body, const std::vector<Argument>& args);
		Function(const Statement& body, const std::vector<const char*>& args, int);

		Function() = default;
		~Function() = default;
		Value call(const std::vector<Value>& callArgs, Module& module);
		Value call(const std::vector<Value>& callArgs, const StringMap<Value>& specifiedArgs, Module& module);
		size_t getArgsCount() const;
		bool hasVariadic() const;
	};

}

#endif // _FUNCTION_