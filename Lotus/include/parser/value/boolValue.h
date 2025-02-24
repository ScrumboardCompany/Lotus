#pragma once

#ifndef _BOOLVALUE_
#define _BOOLVALUE_

#include "parser/value/value.h"

namespace lotus {

	class BoolValue : public IValue {
		bool value;

	public:

		BoolValue(bool value);

		int asInt(Module& module) override;
		double asDouble(Module& module) override;
		bool asBool(Module& module) override;
		String asString(Module& module) override;

		Value add(const Value& other, Module& module) override;
		Value substract(const Value& other, Module& module) override;
		Value multiply(const Value& other, Module& module) override;
		Value divide(const Value& other, Module& module) override;
		Value power(const Value& other, Module& module) override;
		Value divideModule(const Value& other, Module& module) override;

		Value bitwiseAnd(const Value& other, Module& module) override;
		Value bitwiseOr(const Value& other, Module& module) override;
		Value bitwiseXor(const Value& other, Module& module) override;
		Value bitwiseNot(Module& module) override;
		Value bitwiseLeftShift(const Value& other, Module& module) override;
		Value bitwiseRightShift(const Value& other, Module& module) override;

		Value greater(const Value& other, Module& module) override;
		Value less(const Value& other, Module& module) override;
		Value greaterEqual(const Value& other, Module& module) override;
		Value lessEqual(const Value& other, Module& module) override;
		Value equality(const Value& other, Module& module) override;
		Value inequality(const Value& other, Module& module) override;
		Value logicalOr(const Value& other, Module& module) override;
		Value logicalAnd(const Value& other, Module& module) override;

		Value unaryPlus(Module& module) override;
		Value unaryMinus(Module& module) override;
		Value unaryNot(Module& module) override;

		Value sizeInRam() override;
	};

}

#endif // _BOOLVALUE_