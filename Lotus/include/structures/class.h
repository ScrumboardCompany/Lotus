#pragma once

#ifndef _CLASS_
#define _CLASS_

#include "structures/static.h"

namespace lotus {

	class Classes;
	class Functions;

	struct Class {

		Class() = default;

		void setName(const String& name);
		void setName(const char* name);

		void addField(const String& name, const FieldMemberInfo& memberInfo);
		void addMethod(const String& name, const MethodMemberInfo& memberInfo);
		void addField(const char* name, const FieldMemberInfo& memberInfo);
		void addMethod(const char* name, const MethodMemberInfo& memberInfo);

		Value& getField(const String& name);
		Value& getField(const char* name);
		Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables);
		Value callMethod(const char* name, const std::vector<Value>& args, Variables& variables);

	protected:
		ClassValue value;
	private:
		friend class ClassStatement;
		friend class Classes;

		void registerClass(Functions& functions, Variables& variables);
		Function makeDefaultConstructor();
	};
}

#endif // _CLASS_