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

#endif // _OBJECTVALUE_