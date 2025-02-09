#pragma once

#ifndef _UNDEFINEDVALUE_
#define _UNDEFINEDVALUE_

#include "parser/value/value.h"

namespace lotus {

	class UndefinedValue : public IValue {
	public:

		UndefinedValue() = default;

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

#endif // _UNDEFINEDVALUE_