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
		String asString() override;

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