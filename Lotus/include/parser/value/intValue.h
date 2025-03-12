#pragma once

#ifndef _INTVALUE_
#define _INTVALUE_

#include "parser/value/value.h"

namespace lotus {

	class IntValue : public IValue {
		Int value;

	public:

		IntValue(Int value);

		Int asInt(Module&) override;
		double asDouble(Module&) override;
		bool asBool(Module&) override;
		String asString(Module&) override;

		Value add(const Value& other, Module& module) override;
		Value substract(const Value& other, Module& module) override;
		Value multiply(const Value& other, Module& module) override;
		Value divide(const Value& other, Module& module) override;
		Value power(const Value& other, Module& module) override;
		Value divideModule(const Value& other, Module& module) override;

		Value bitwiseAnd(const Value& other, Module& module) override;
		Value bitwiseOr(const Value& other, Module& module) override;
		Value bitwiseXor(const Value& other, Module& module) override;
		Value bitwiseNot(Module&) override;
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

		Value addSet(const Value& other, Module& module) override;
		Value substractSet(const Value& other, Module& module) override;
		Value multiplySet(const Value& other, Module& module) override;
		Value divideSet(const Value& other, Module& module) override;
		Value powerSet(const Value& other, Module& module) override;
		Value divideModuleSet(const Value& other, Module& module) override;
		Value bitwiseAndSet(const Value& other, Module& module) override;
		Value bitwiseOrSet(const Value& other, Module& module) override;
		Value bitwiseXorSet(const Value& other, Module& module) override;
		Value bitwiseNotSet(Module& module) override;
		Value bitwiseLeftShiftSet(const Value& other, Module& module) override;
		Value bitwiseRightShiftSet(const Value& other, Module& module) override;

		Value unaryPlus(Module&) override;
		Value unaryMinus(Module&) override;
		Value unaryNot(Module&) override;
		Value prefixIncrement(Module&) override;
		Value postfixIncrement(Module&) override;
		Value prefixDecrement(Module&) override;
		Value postfixDecrement(Module&) override;

		Value size(Module&) override;
		Value sizeInRam() override;
	};

}

#endif // _INTVALUE_