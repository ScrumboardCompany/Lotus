#pragma once

#ifndef _UNDEFINEDVALUE_
#define _UNDEFINEDVALUE_

#include "parser/value/value.h"

namespace lotus {

	class UndefinedValue : public IValue {
	public:

		UndefinedValue();

		int asInt(Module&) override;
		double asDouble(Module&) override;
		bool asBool(Module&) override;
		String asString(Module&) override;

		Value sizeInRam() override;
	};

}

#endif // _UNDEFINEDVALUE_