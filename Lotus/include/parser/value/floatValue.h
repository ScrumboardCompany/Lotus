#pragma once

#ifndef _FLOATVALUE_
#define _FLOATVALUE_

#include "parser/value/value.h"

namespace lotus {

	class FloatValue : public IValue {
		double value;

	public:

		FloatValue(double value);

		int asInt() override;
		double asDouble() override;
		bool asBool() override;
		String asString() override;

		String getType() const override;

		Value add(const Value& other) override;
		Value substract(const Value& other) override;
		Value multiply(const Value& other) override;
		Value divide(const Value& other) override;

		Value greater(const Value& other) override;
		Value less(const Value& other) override;
		Value greaterEqual(const Value& other) override;
		Value lessEqual(const Value& other) override;
		Value equality(const Value& other) override;
		Value inequality(const Value& other) override;
		Value logicalOr(const Value& other) override;
		Value logicalAnd(const Value& other) override;

		Value unaryPlus() override;
		Value unaryMinus() override;
		Value unaryNot() override;
	};

}

#endif // _INTVALUE_