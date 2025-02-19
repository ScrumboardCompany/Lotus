#pragma once

#ifndef _CLASSVALUE_
#define _CLASSVALUE_

#include "parser/value/value.h"
#include "parser/function/function.h"
#include "structures/classStructures.h"

namespace lotus {

	class ClassValue : public IValue {
		friend class ClassStatement;
		friend class ObjectExpression;

	public:

		ClassValue() = default;

		Value& getField(const String& name) override;
		Value callMethod(const String& name, const std::vector<Value>& args, Variables& variables) override;

		Value sizeInRam() override;

	protected:
		Fields_t fields;
		Methods_t methods;
	};

}

#endif // _CLASSVALUE_