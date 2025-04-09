#pragma once

#ifndef _ARRAYVALUE_
#define _ARRAYVALUE_

#include "parser/value/classValue.h"

namespace lotus {

	class LOTUS_API ArrayValue : public ClassValue {
		std::vector<Value> elements;

	public:

		ArrayValue(const std::vector<Value>& elements);

		ArrayValue(ArrayValue&&) = default;

		String asString(Module& module) override;

		Value add(const Value& other, Module& module) override;

		Value addSet(const Value& other, Module& module) override;

		void foreach(const String& name, const Statement& body, Module& module) override;
		Value getOfIndex(const Value& index, Module& module) override;
		Value setOfIndex(const Value& index, const Value& other, Module& module) override;
		Value size(Module&) override;
		Value sizeInRam() override;
	};

	LOTUS_API Value ARRAY(const std::vector<Value>& elements);

}

#endif // _ARRAYVALUE_