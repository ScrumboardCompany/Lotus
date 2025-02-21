#pragma once

#ifndef _CLASSVALUE_
#define _CLASSVALUE_

#include "parser/value/value.h"
#include "parser/function/function.h"
#include "structures/classStructures.h"

namespace lotus {

	class ClassValue : public IValue {
		friend class ClassStatement;
		friend class ObjectExpression;

		MethodMemberInfo getMethod(const String& name, size_t argsCount);

		std::vector<ClassValue> parents;

		void collectInheritedMembers(ClassValue& thisValue);

		bool hasField(const String& name);

		bool assignField(const String& name, const FieldMemberInfo& field);

	public:

		ClassValue() = default;

		void declareField(const String& name, const FieldMemberInfo& memberInfo);
		void declareMethod(const String& name, const MethodMemberInfo& memberInfo);

		Value& getField(const String& name) override;
		Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables) override;

		Value sizeInRam() override;

	protected:
		Fields_t fields;
		Methods_t methods;
	};

}

#endif // _CLASSVALUE_