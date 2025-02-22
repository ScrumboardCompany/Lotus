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

		String asString() override;

		Value add(const Value& other) override;

		Value addSet(const Value& other) override;

		void foreach(const String& name, const Statement& body, Variables& variables) override;
		Value& index(const Value& index) override;
		Value size() override;
		Value sizeInRam() override;
	};

}

#endif // _OBJECTVALUE_