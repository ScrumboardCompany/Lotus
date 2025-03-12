#pragma once

#ifndef _ENUMVALUE_
#define _ENUMVALUE_

#include "parser/value/value.h"
#include <functional>

namespace lotus {

	class EnumValue : public IValue {
		Value value;

		Value checkIsEnumAndCompare(const Value& other, Module& module, const std::function<Value(EnumValue, Module&)>& operation);

	public:

		EnumValue(const Value& value, const String& type);

		Int asInt(Module& module) override;
		String asString(Module& module) override;

		Value greater(const Value& other, Module& module) override;
		Value less(const Value& other, Module& module) override;
		Value greaterEqual(const Value& other, Module& module) override;
		Value lessEqual(const Value& other, Module& module) override;
		Value equality(const Value& other, Module& module) override;
		Value inequality(const Value& other, Module& module) override;
		Value logicalOr(const Value& other, Module& module) override;
		Value logicalAnd(const Value& other, Module& module) override;

		Value sizeInRam() override;
	};

}

#endif // _ENUMVALUE_