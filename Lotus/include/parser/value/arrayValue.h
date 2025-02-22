#pragma once

#ifndef _ARRAYVALUE_
#define _ARRAYVALUE_

#include "parser/value/value.h"

namespace lotus {

	class ArrayValue : public IValue {
		std::vector<Value> elements;

	public:

		ArrayValue(std::vector<Value> elements);

		String asString(Variables& variables) override;

		Value add(const Value& other, Variables& variables) override;

		Value addSet(const Value& other, Variables& variables) override;

		void foreach(const String& name, const Statement& body, Variables& variables) override;
		Value getOfIndex(const Value& index, Variables& variables) override;
		Value setOfIndex(const Value& index, const Value& other, Variables& variables) override;
		Value size(Variables& variables) override;
		Value sizeInRam() override;
	};

}

#endif // _ARRAYVALUE_