#pragma once

#ifndef _VARIABLES_
#define _VARIABLES_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/value/undefinedValue.h"

#include <stack>

namespace lotus {

	class Variables {
		StringMap<Value> variables;
		std::stack<StringMap<Value>> savedStates;
		friend class ImportStatement;

	public:
		Variables() = default;

		void forceDeclareOrSet(const String& name, const Value& value = UNDEFINED());

		void declare(const String& name, const Value& value = UNDEFINED());

		void set(const String& name, const Value& value);

		Value& get(const String& name);

		bool isExists(const String& name);

		void saveState();
		void restoreState();
	};

}

#endif // _VARIABLES_