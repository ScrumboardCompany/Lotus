#pragma once

#ifndef _STRINGVALUE_
#define _STRINGVALUE_

#include "parser/value/value.h"

namespace lotus {

	class StringValue : public IValue {
		String value;

	public:

		StringValue(const char* value);
		StringValue(const String& value);

		int asInt(Module& module) override;
		double asDouble(Module& module) override;
		bool asBool(Module& module) override;
		String asString(Module& module) override;

		Value add(const Value& other, Module& module) override;
		Value multiply(const Value& other, Module& module) override;

		Value greater(const Value& other, Module& module) override;
		Value less(const Value& other, Module& module) override;
		Value greaterEqual(const Value& other, Module& module) override;
		Value lessEqual(const Value& other, Module& module) override;
		Value equality(const Value& other, Module& module) override;
		Value inequality(const Value& other, Module& module) override;
		Value logicalOr(const Value& other, Module& module) override;
		Value logicalAnd(const Value& other, Module& module) override;

		Value addSet(const Value& other, Module& module) override;
		Value multiplySet(const Value& other, Module& module) override;

		Value getOfIndex(const Value& index, Module& module) override;
		Value setOfIndex(const Value& index, const Value& other, Module& module) override;
		Value size(Module& module) override;
		Value sizeInRam() override;
	};

}

#endif // _STRINGVALUE_