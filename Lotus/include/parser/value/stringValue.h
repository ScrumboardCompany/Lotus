#pragma once

#ifndef _STRINGVALUE_
#define _STRINGVALUE_

#include "parser/value/value.h"

namespace lotus {

	class StringCharReference;

	class StringValue : public IValue {
		String value;
		Value tempRef;

		friend class StringCharReference;

	public:

		StringValue(const String& value);

		int asInt() override;
		double asDouble() override;
		bool asBool() override;
		String asString() override;

		String getType() const override;

		Value add(const Value& other) override;
		Value multiply(const Value& other) override;

		Value greater(const Value& other) override;
		Value less(const Value& other) override;
		Value greaterEqual(const Value& other) override;
		Value lessEqual(const Value& other) override;
		Value equality(const Value& other) override;
		Value inequality(const Value& other) override;
		Value logicalOr(const Value& other) override;
		Value logicalAnd(const Value& other) override;

		Value addSet(const Value& other) override;
		Value multiplySet(const Value& other) override;

		Value& index(const Value& index) override;
		Value size() override;
	};

}

#endif // _STRINGVALUE_