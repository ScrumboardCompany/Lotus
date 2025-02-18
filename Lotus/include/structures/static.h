#pragma once

#ifndef _STATIC_
#define _STATIC_

#include "structures/classStructures.h"

namespace lotus {

	struct Static {
		Fields_t fields;
		Methods_t methods;

		void addField(const String& name, const FieldMemberInfo& memberInfo);
		void addMethod(const String& name, const MethodMemberInfo& memberInfo);
		void addField(const char* name, const FieldMemberInfo& memberInfo);
		void addMethod(const char* name, const MethodMemberInfo& memberInfo);

		Value& getField(const String& name);
		Value& getField(const char* name);
		Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables);
		Value callMethod(const char* name, const std::vector<Value>& args, Variables& variables);
	};
}

#endif // _STATICS_