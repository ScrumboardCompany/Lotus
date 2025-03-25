#pragma once

#ifndef _UNDEFINEDVALUE_
#define _UNDEFINEDVALUE_

#include "parser/value/value.h"

namespace lotus {

	class LOTUS_API UndefinedValue : public IValue {
	public:

		UndefinedValue();

		Int asInt(Module&) override;
		double asDouble(Module&) override;
		bool asBool(Module&) override;
		String asString(Module&) override;

		Value sizeInRam() override;
	};

	LOTUS_API Value UNDEFINED();

}

#endif // _UNDEFINEDVALUE_