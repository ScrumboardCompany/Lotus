#pragma once

#ifndef _STRINGVALUE_
#define _STRINGVALUE_

#include "parser/value/value.h"

namespace lotus {

	class StringValue : public IValue {
		String value;

	public:

		StringValue(const String& value);

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

#endif // _STRINGVALUE_