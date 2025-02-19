#pragma once

#ifndef _STATIC_
#define _STATIC_

#include "structures/classStructures.h"
#include "parser/value/classValue.h"

namespace lotus {

	struct Static {

		void addField(const String& name, const FieldMemberInfo& memberInfo);
		void addMethod(const String& name, const MethodMemberInfo& memberInfo);
		void addField(const char* name, const FieldMemberInfo& memberInfo);
		void addMethod(const char* name, const MethodMemberInfo& memberInfo);

		Value& getField(const String& name);
		Value& getField(const char* name);
		Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables);
		Value callMethod(const char* name, const std::vector<Value>& args, Variables& variables);

	private:
		ClassValue value;
	};
}

#endif // _STATICS_