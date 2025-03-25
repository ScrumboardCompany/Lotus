#pragma once

#ifndef _VARIABLES_
#define _VARIABLES_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/value/undefinedValue.h"
#include <vector>

namespace lotus {

	class LOTUS_API Variables {
	public:
		StringMap<Value> variables;
		std::vector<StringMap<Value>> scopes;
		friend class ImportStatement;
		friend class ClassValue;

		Variables() {
			enterScope();
		}

		void forceSet(const String& name, const Value& value = UNDEFINED());

		void forceSet(const char* name, const Value& value = UNDEFINED());

		void declare(const String& name, const Value& value = UNDEFINED());

		void declare(const char* name, const Value& value = UNDEFINED());

		void set(const String& name, const Value& value);

		void set(const char* name, const Value& value);

		Value& get(const String& name);

		Value& get(const char* name);

		bool isExists(const String& name) const;

		bool isExists(const char* name) const;

		void enterScope(); 
		void exitScope();

		size_t scopesCount() const;
	};

}

#endif // _VARIABLES_
