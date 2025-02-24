#pragma once

#ifndef _ARRAYVALUE_
#define _ARRAYVALUE_

#include "parser/value/value.h"

namespace lotus {

	class ArrayValue : public IValue {
		std::vector<Value> elements;

	public:

		ArrayValue(std::vector<Value> elements);

		String asString(Module& module) override;

		Value add(const Value& other, Module& module) override;

		Value addSet(const Value& other, Module& module) override;

		void foreach(const String& name, const Statement& body, Module& module) override;
		Value getOfIndex(const Value& index, Module& module) override;
		Value setOfIndex(const Value& index, const Value& other, Module& module) override;
		Value size(Module& module) override;
		Value sizeInRam() override;
	};

}

#endif // _ARRAYVALUE_