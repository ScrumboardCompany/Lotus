#pragma once

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/value/undefinedValue.h"
#include "parser/function/function.h"

namespace lotus {

	class Functions {

		StringMap<std::vector<Function>> functions;

		friend class ImportStatement;

	public:
		Functions() = default;

		void forceSet(const String& name, const Function& value);

		void forceSet(const char* name, const Function& value);

		void declare(const String& name, const Function& value);

		void declare(const char* name, const Function& value);

		void set(const String& name, const Function& value);

		void set(const char* name, const Function& value);

		Function get(const String& name, size_t argsCount = 0);

		Function get(const char* name, size_t argsCount = 0);

		Value call(const String& name, const std::vector<Value>& args, Module& module);

		Value call(const char* name, const std::vector<Value>& args, Module& module);

		Value call(const String& name, const std::vector<Value>& args, const StringMap<Value>& specifiedArgs, Module& module);

		Value call(const char* name, const std::vector<Value>& args, const StringMap<Value>& specifiedArgs, Module& module);

		bool isExists(const String& name);

		bool isExists(const char* name);
	};

}

#endif // _FUNCTIONS_