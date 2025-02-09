#pragma once

#ifndef _VARIABLES_
#define _VARIABLES_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/value/undefinedValue.h"

namespace lotus {

	class Variables {
		StringMap<Value> variables;
	public:
		Variables() = default;

		void declare(const String& name, const Value& value = UNDEFINED());

		void set(const String& name, const Value& value);

		Value get(const String& name);

		bool isExists(const String& name);
	};

}

#endif // _VARIABLES_