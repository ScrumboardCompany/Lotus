#pragma once

#ifndef _OBJECTVALUE_
#define _OBJECTVALUE_

#include "parser/value/value.h"

namespace lotus {

	class ObjectValue : public IValue {
		StringMap<Value> fields;

	public:

		ObjectValue(const StringMap<Value>& fields);

		Value& getField(const String& name) override;

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

#endif // _OBJECTVALUE_