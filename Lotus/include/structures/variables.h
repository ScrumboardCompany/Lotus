#pragma once

#ifndef _VARIABLES_
#define _VARIABLES_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/value/undefinedValue.h"
#include <stack>
#include <vector>

namespace lotus {

	class Variables {
		StringMap<Value> variables;
		std::vector<StringMap<Value>> scopes;
		friend class ImportStatement;
		friend class ClassValue;

	public:
		Variables() {
			enterScope();
		}

		void forceDeclareOrSet(const String& name, const Value& value = UNDEFINED());

		void forceDeclareOrSet(const char* name, const Value& value = UNDEFINED());

		void declare(const String& name, const Value& value = UNDEFINED());

		void declare(const char* name, const Value& value = UNDEFINED());

		void set(const String& name, const Value& value);

		void set(const char* name, const Value& value);

		Value& get(const String& name);

		Value& get(const char* name);

		bool isExists(const String& name);

		bool isExists(const char* name);

		void enterScope(); 
		void exitScope();
	};

}

#endif // _VARIABLES_
