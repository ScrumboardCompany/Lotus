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

		String getType() const override;

		Value add(const Value& other) override;
		Value substract(const Value& other) override;
		Value multiply(const Value& other) override;
		Value divide(const Value& other) override;

		Value unary_plus() override;
		Value unary_minus() override;
	};

}

#endif // _INTVALUE_