#pragma once

#ifndef _BOOLVALUE_
#define _BOOLVALUE_

#include "parser/value/value.h"

namespace lotus {

	class BoolValue : public IValue {
		bool value;

	public:

		BoolValue(bool value);

		Int asInt(Module&) override;
		double asDouble(Module&) override;
		bool asBool(Module&) override;
		String asString(Module&) override;

		Value equality(const Value& other, Module& module) override;
		Value inequality(const Value& other, Module& module) override;
		Value logicalOr(const Value& other, Module& module) override;
		Value logicalAnd(const Value& other, Module& module) override;

		Value unaryPlus(Module& module) override;
		Value unaryMinus(Module& module) override;
		Value unaryNot(Module&) override;

		Value sizeInRam() override;
	};

}

#endif // _BOOLVALUE_