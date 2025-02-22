#pragma once

#ifndef _BOOLVALUE_
#define _BOOLVALUE_

#include "parser/value/value.h"

namespace lotus {

	class BoolValue : public IValue {
		bool value;

	public:

		BoolValue(bool value);

		int asInt(Variables& variables) override;
		double asDouble(Variables& variables) override;
		bool asBool(Variables& variables) override;
		String asString(Variables& variables) override;

		Value add(const Value& other, Variables& variables) override;
		Value substract(const Value& other, Variables& variables) override;
		Value multiply(const Value& other, Variables& variables) override;
		Value divide(const Value& other, Variables& variables) override;
		Value power(const Value& other, Variables& variables) override;
		Value divideModule(const Value& other, Variables& variables) override;

		Value bitwiseAnd(const Value& other, Variables& variables) override;
		Value bitwiseOr(const Value& other, Variables& variables) override;
		Value bitwiseXor(const Value& other, Variables& variables) override;
		Value bitwiseNot(Variables& variables) override;
		Value bitwiseLeftShift(const Value& other, Variables& variables) override;
		Value bitwiseRightShift(const Value& other, Variables& variables) override;

		Value greater(const Value& other, Variables& variables) override;
		Value less(const Value& other, Variables& variables) override;
		Value greaterEqual(const Value& other, Variables& variables) override;
		Value lessEqual(const Value& other, Variables& variables) override;
		Value equality(const Value& other, Variables& variables) override;
		Value inequality(const Value& other, Variables& variables) override;
		Value logicalOr(const Value& other, Variables& variables) override;
		Value logicalAnd(const Value& other, Variables& variables) override;

		Value unaryPlus(Variables& variables) override;
		Value unaryMinus(Variables& variables) override;
		Value unaryNot(Variables& variables) override;

		Value sizeInRam() override;
	};

}

#endif // _BOOLVALUE_