#pragma once

#ifndef _CLASSVALUE_
#define _CLASSVALUE_

#include "parser/value/value.h"
#include "structures/classStructures.h"

namespace lotus {

	class ClassValue : public IValue {
		friend class ClassStatement;
		friend class ObjectExpression;
		friend struct Class;

		ClassValue& getMethod(const String& name, size_t argsCount, MethodMemberInfo& memberInfo, Ptr<FieldMemberInfo> field);

		std::vector<Ptr<ClassValue>> parents;

		bool hasField(const String& name);

		void protectedToPublicInParents(StringMap<AccessModifierType>& accessModifiers);

		void publicToProtectedInParents(const StringMap<AccessModifierType>& accessModifiers, bool needThis = true);

		void calculateSizeInRam(Int& size);

	public:

		ClassValue() = default;

		virtual Int asInt(Module& module) override;
		virtual double asDouble(Module& module) override;
		virtual bool asBool(Module& module) override;
		virtual String asString(Module& module) override;

		virtual Value add(const Value& other, Module& module) override;
		virtual Value substract(const Value& other, Module& module) override;
		virtual Value multiply(const Value& other, Module& module) override;
		virtual Value divide(const Value& other, Module& module) override;
		virtual Value power(const Value& other, Module& module) override;
		virtual Value divideModule(const Value& other, Module& module) override;

		virtual Value bitwiseAnd(const Value& other, Module& module) override;
		virtual Value bitwiseOr(const Value& other, Module& module) override;
		virtual Value bitwiseXor(const Value& other, Module& module) override;
		virtual Value bitwiseNot(Module& module) override;
		virtual Value bitwiseLeftShift(const Value& other, Module& module) override;
		virtual Value bitwiseRightShift(const Value& other, Module& module) override;

		virtual Value greater(const Value& other, Module& module) override;
		virtual Value less(const Value& other, Module& module) override;
		virtual Value greaterEqual(const Value& other, Module& module) override;
		virtual Value lessEqual(const Value& other, Module& module) override;
		virtual Value equality(const Value& other, Module& module) override;
		virtual Value inequality(const Value& other, Module& module) override;
		virtual Value logicalOr(const Value& other, Module& module) override;
		virtual Value logicalAnd(const Value& other, Module& module) override;

		virtual Value addSet(const Value& other, Module& module) override;
		virtual Value substractSet(const Value& other, Module& module) override;
		virtual Value multiplySet(const Value& other, Module& module) override;
		virtual Value divideSet(const Value& other, Module& module) override;
		virtual Value powerSet(const Value& other, Module& module) override;
		virtual Value divideModuleSet(const Value& other, Module& module) override;
		virtual Value bitwiseAndSet(const Value& other, Module& module) override;
		virtual Value bitwiseOrSet(const Value& other, Module& module) override;
		virtual Value bitwiseXorSet(const Value& other, Module& module) override;
		virtual Value bitwiseNotSet(Module& module) override;
		virtual Value bitwiseLeftShiftSet(const Value& other, Module& module) override;
		virtual Value bitwiseRightShiftSet(const Value& other, Module& module) override;

		virtual Value unaryPlus(Module& module) override;
		virtual Value unaryMinus(Module& module) override;
		virtual Value unaryNot(Module& module) override;
		virtual Value prefixIncrement(Module& module) override;
		virtual Value postfixIncrement(Module& module) override;
		virtual Value prefixDecrement(Module& module) override;
		virtual Value postfixDecrement(Module& module) override;

		virtual Value size(Module& module) override;
		virtual Value getOfIndex(const Value& index, Module& module) override;
		virtual Value setOfIndex(const Value& index, const Value& other, Module& module) override;

		void declareField(const String& name, const FieldMemberInfo& memberInfo);
		void declareMethod(const String& name, const MethodMemberInfo& memberInfo);

		Value& getField(const String& name) override;
		Value callMethod(const String& name, const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs = {}) override;
		virtual Value call(const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs = {}) override;

		Value sizeInRam() override;

	protected:
		Fields_t fields;
		Methods_t methods;
	};

}

#endif // _CLASSVALUE_