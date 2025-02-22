#pragma once

#ifndef _VALUE_
#define _VALUE_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Function;
	class Variables;

	class IValue {
	public:

		virtual int asInt(Variables& variables);
		virtual double asDouble(Variables& variables);
		virtual bool asBool(Variables& variables);
		virtual String asString(Variables& variables);

		String getType() const;
		virtual Value& getField(const String& name);
		virtual Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables);
		virtual Value call(const std::vector<Value>& args, Variables& variables);

		virtual Value add(const Value& other, Variables& variables);
		virtual Value substract(const Value& other, Variables& variables);
		virtual Value multiply(const Value& other, Variables& variables);
		virtual Value divide(const Value& other, Variables& variables);
		virtual Value power(const Value& other, Variables& variables);
		virtual Value divideModule(const Value& other, Variables& variables);

		virtual Value bitwiseAnd(const Value& other, Variables& variables);
		virtual Value bitwiseOr(const Value& other, Variables& variables);
		virtual Value bitwiseXor(const Value& other, Variables& variables);
		virtual Value bitwiseNot(Variables& variables);
		virtual Value bitwiseLeftShift(const Value& other, Variables& variables);
		virtual Value bitwiseRightShift(const Value& other, Variables& variables);

		virtual Value greater(const Value& other, Variables& variables);
		virtual Value less(const Value& other, Variables& variables);
		virtual Value greaterEqual(const Value& other, Variables& variables);
		virtual Value lessEqual(const Value& other, Variables& variables);
		virtual Value equality(const Value& other, Variables& variables);
		virtual Value inequality(const Value& other, Variables& variables);
		virtual Value logicalOr(const Value& other, Variables& variables);
		virtual Value logicalAnd(const Value& other, Variables& variables);

		virtual Value addSet(const Value& other, Variables& variables);
		virtual Value substractSet(const Value& other, Variables& variables);
		virtual Value multiplySet(const Value& other, Variables& variables);
		virtual Value divideSet(const Value& other, Variables& variables);
		virtual Value powerSet(const Value& other, Variables& variables);
		virtual Value divideModuleSet(const Value& other, Variables& variables);
		virtual Value bitwiseAndSet(const Value& other, Variables& variables);
		virtual Value bitwiseOrSet(const Value& other, Variables& variables);
		virtual Value bitwiseXorSet(const Value& other, Variables& variables);
		virtual Value bitwiseNotSet(Variables& variables);
		virtual Value bitwiseLeftShiftSet(const Value& other, Variables& variables);
		virtual Value bitwiseRightShiftSet(const Value& other, Variables& variables);

		virtual Value unaryPlus(Variables& variables);
		virtual Value unaryMinus(Variables& variables);
		virtual Value unaryNot(Variables& variables);
		virtual Value prefixIncrement(Variables& variables);
		virtual Value postfixIncrement(Variables& variables);
		virtual Value prefixDecrement(Variables& variables);
		virtual Value postfixDecrement(Variables& variables);

		virtual void foreach(const String& name, const Statement& body, Variables& variables);
		virtual Value getOfIndex(const Value& index, Variables& variables);
		virtual Value setOfIndex(const Value& index, const Value& other, Variables& variables);
		virtual Value size(Variables& variables);
		virtual Value sizeInRam() = 0;

		virtual ~IValue() = default;

		friend class ClassStatement;
		friend class ObjectExpression;

	protected:

		String type;
	};
}

#endif // _VALUE_