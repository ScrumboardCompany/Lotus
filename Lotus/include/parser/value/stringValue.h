#pragma once

#ifndef _STRINGVALUE_
#define _STRINGVALUE_

#include "parser/value/value.h"

namespace lotus {

	class LOTUS_API StringValue : public IValue {
		String value;

	public:

		StringValue(const char* value);
		StringValue(const String& value);
		StringValue() = default;

		Int asInt(Module&) override;
		double asDouble(Module&) override;
		bool asBool(Module&) override;
		String asString(Module&) override;

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
		Value size(Module&) override;
		Value sizeInRam() override;
	};

	LOTUS_API Value STRING(const char* value);

	LOTUS_API Value STRING(const String& value);

	LOTUS_API Value STRING();

}

#endif // _STRINGVALUE_