#pragma once

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/value/undefinedValue.h"
#include "parser/function/function.h"

namespace lotus {

	class Functions {
		StringMap<Function> functions;

		friend class ImportStatement;

	public:
		Functions() = default;

		void forceDeclareOrSet(const String& name, const Function& value);

		void declare(const String& name, const Function& value);

		void set(const String& name, const Function& value);

		Function get(const String& name);

		Value call(const String& name, const std::vector<Value>& args, Variables& variables);

		bool isExists(const String& name);
	};

}

#endif // _FUNCTIONS_