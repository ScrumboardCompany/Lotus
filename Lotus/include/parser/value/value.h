#pragma once

#ifndef _VALUE_
#define _VALUE_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"

namespace lotus {

	class Function;
	struct Module;

	class LOTUS_API IValue {
	public:

		virtual Int asInt(Module& module);
		virtual double asDouble(Module& module);
		virtual bool asBool(Module& module);
		virtual String asString(Module& module);

		String getType() const;
		bool instanceOf(const String& type) const;
		bool instanceOf(const char* type) const;
		virtual Value& getField(const String& name);
		virtual Value& getField(const char* name);
		virtual Value callMethod(const String& name, const std::vector<Value>&, Module&, const StringMap<Value>& = {});
		virtual Value callMethod(const char* name, const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs = {});
		virtual Value call(const std::vector<Value>&, Module&, const StringMap<Value>& = {});

		virtual Value add(const Value& other, Module& module);
		virtual Value substract(const Value& other, Module& module);
		virtual Value multiply(const Value& other, Module& module);
		virtual Value divide(const Value& other, Module& module);
		virtual Value power(const Value& other, Module& module);
		virtual Value divideModule(const Value& other, Module& module);

		virtual Value bitwiseAnd(const Value& other, Module& module);
		virtual Value bitwiseOr(const Value& other, Module& module);
		virtual Value bitwiseXor(const Value& other, Module& module);
		virtual Value bitwiseNot(Module& module);
		virtual Value bitwiseLeftShift(const Value& other, Module& module);
		virtual Value bitwiseRightShift(const Value& other, Module& module);

		virtual Value greater(const Value& other, Module& module);
		virtual Value less(const Value& other, Module& module);
		virtual Value greaterEqual(const Value& other, Module& module);
		virtual Value lessEqual(const Value& other, Module& module);
		virtual Value equality(const Value& other, Module& module);
		virtual Value inequality(const Value& other, Module& module);
		virtual Value logicalOr(const Value& other, Module& module);
		virtual Value logicalAnd(const Value& other, Module& module);

		virtual Value addSet(const Value& other, Module& module);
		virtual Value substractSet(const Value& other, Module& module);
		virtual Value multiplySet(const Value& other, Module& module);
		virtual Value divideSet(const Value& other, Module& module);
		virtual Value powerSet(const Value& other, Module& module);
		virtual Value divideModuleSet(const Value& other, Module& module);
		virtual Value bitwiseAndSet(const Value& other, Module& module);
		virtual Value bitwiseOrSet(const Value& other, Module& module);
		virtual Value bitwiseXorSet(const Value& other, Module& module);
		virtual Value bitwiseNotSet(Module& module);
		virtual Value bitwiseLeftShiftSet(const Value& other, Module& module);
		virtual Value bitwiseRightShiftSet(const Value& other, Module& module);

		virtual Value unaryPlus(Module& module);
		virtual Value unaryMinus(Module& module);
		virtual Value unaryNot(Module& module);
		virtual Value prefixIncrement(Module& module);
		virtual Value postfixIncrement(Module& module);
		virtual Value prefixDecrement(Module& module);
		virtual Value postfixDecrement(Module& module);

		virtual void foreach(const String& name, const Statement& body, Module& module);
		virtual Value getOfIndex(const Value& index, Module& module);
		virtual Value setOfIndex(const Value& index, const Value& other, Module& module);
		virtual Value size(Module& module);
		virtual Value sizeInRam() = 0;

		virtual ~IValue() = default;

		friend class ClassStatement;
		friend class ObjectExpression;

	protected:

		String type;
	};
}

#endif // _VALUE_