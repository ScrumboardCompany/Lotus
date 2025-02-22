#pragma once

#ifndef _STRINGVALUE_
#define _STRINGVALUE_

#include "parser/value/value.h"

namespace lotus {

	class StringValue : public IValue {
		String value;

	public:

		StringValue(const String& value);

		int asInt(Variables& variables) override;
		double asDouble(Variables& variables) override;
		bool asBool(Variables& variables) override;
		String asString(Variables& variables) override;

		Value add(const Value& other, Variables& variables) override;
		Value multiply(const Value& other, Variables& variables) override;

		Value greater(const Value& other, Variables& variables) override;
		Value less(const Value& other, Variables& variables) override;
		Value greaterEqual(const Value& other, Variables& variables) override;
		Value lessEqual(const Value& other, Variables& variables) override;
		Value equality(const Value& other, Variables& variables) override;
		Value inequality(const Value& other, Variables& variables) override;
		Value logicalOr(const Value& other, Variables& variables) override;
		Value logicalAnd(const Value& other, Variables& variables) override;

		Value addSet(const Value& other, Variables& variables) override;
		Value multiplySet(const Value& other, Variables& variables) override;

		Value getOfIndex(const Value& index, Variables& variables) override;
		Value setOfIndex(const Value& index, const Value& other, Variables& variables) override;
		Value size(Variables& variables) override;
		Value sizeInRam() override;
	};

}

#endif // _STRINGVALUE_