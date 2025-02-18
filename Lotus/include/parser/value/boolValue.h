#pragma once

#ifndef _BOOLVALUE_
#define _BOOLVALUE_

#include "parser/value/value.h"

namespace lotus {

	class BoolValue : public IValue {
		bool value;

	public:

		BoolValue(bool value);

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

		Value bitwiseAnd(const Value& other) override;
		Value bitwiseOr(const Value& other) override;
		Value bitwiseXor(const Value& other) override;
		Value bitwiseNot() override;
		Value bitwiseLeftShift(const Value& other) override;
		Value bitwiseRightShift(const Value& other) override;

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

		Value sizeInRam() override;
	};

}

#endif // _BOOLVALUE_