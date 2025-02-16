#pragma once

#ifndef _INTVALUE_
#define _INTVALUE_

#include "parser/value/value.h"

namespace lotus {

	class IntValue : public IValue {
		int value;

	public:

		IntValue(int value);

		int asInt() override;
		double asDouble() override;
		bool asBool() override;
		String asString() override;

		Value add(const Value& other) override;
		Value substract(const Value& other) override;
		Value multiply(const Value& other) override;
		Value divide(const Value& other) override;
		Value power(const Value& other) override;
		Value divideModule(const Value& other) override;

		Value greater(const Value& other) override;
		Value less(const Value& other) override;
		Value greaterEqual(const Value& other) override;
		Value lessEqual(const Value& other) override;
		Value equality(const Value& other) override;
		Value inequality(const Value& other) override;
		Value logicalOr(const Value& other) override;
		Value logicalAnd(const Value& other) override;

		Value addSet(const Value& other) override;
		Value substractSet(const Value& other) override;
		Value multiplySet(const Value& other) override;
		Value divideSet(const Value& other) override;

		Value unaryPlus() override;
		Value unaryMinus() override;
		Value unaryNot() override;
		Value prefixIncrement() override;
		Value postfixIncrement() override;
		Value prefixDecrement() override;
		Value postfixDecrement() override;

		Value size() override;
		Value sizeInRam() override;
	};

}

#endif // _INTVALUE_