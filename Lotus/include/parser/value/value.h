#pragma once

#ifndef _VALUE_
#define _VALUE_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"

namespace lotus {

	class Function;
	class Variables;

	class IValue {
	public:

		virtual int asInt();
		virtual double asDouble();
		virtual bool asBool();
		virtual String asString();

		String getType() const;
		virtual Value& getField(const String& name);
		virtual Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables);
		virtual Value call(const std::vector<Value>& args, Variables& variables);

		virtual Value add(const Value& other);
		virtual Value substract(const Value& other);
		virtual Value multiply(const Value& other);
		virtual Value divide(const Value& other);
		virtual Value power(const Value& other);
		virtual Value divideModule(const Value& other);

		virtual Value bitwiseAnd(const Value& other);
		virtual Value bitwiseOr(const Value& other);
		virtual Value bitwiseXor(const Value& other);
		virtual Value bitwiseNot();
		virtual Value bitwiseLeftShift(const Value& other);
		virtual Value bitwiseRightShift(const Value& other);

		virtual Value greater(const Value& other);
		virtual Value less(const Value& other);
		virtual Value greaterEqual(const Value& other);
		virtual Value lessEqual(const Value& other);
		virtual Value equality(const Value& other);
		virtual Value inequality(const Value& other);
		virtual Value logicalOr(const Value& other);
		virtual Value logicalAnd(const Value& other);

		virtual Value addSet(const Value& other);
		virtual Value substractSet(const Value& other);
		virtual Value multiplySet(const Value& other);
		virtual Value divideSet(const Value& other);

		virtual Value unaryPlus();
		virtual Value unaryMinus();
		virtual Value unaryNot();
		virtual Value prefixIncrement();
		virtual Value postfixIncrement();
		virtual Value prefixDecrement();
		virtual Value postfixDecrement();

		virtual Value& index(const Value& index);
		virtual Value size();
		virtual Value sizeInRam() = 0;

		virtual ~IValue() = default;

		friend class ClassStatement;
		friend class ObjectExpression;

	protected:

		String type;
	};
}

#endif // _VALUE_