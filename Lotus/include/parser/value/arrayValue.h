#pragma once

#ifndef _ARRAYVALUE_
#define _ARRAYVALUE_

#include "parser/value/value.h"

namespace lotus {

	class ArrayValue : public IValue {
		std::vector<Value> elements;

	public:

		ArrayValue(std::vector<Value> elements);

		String asString() override;

		String getType() const override;

		Value add(const Value& other) override;

		Value addSet(const Value& other) override;

		Value& index(const Value& index) override;
		Value size() override;
	};

}

#endif // _ARRAYVALUE_