#pragma once

#ifndef _UNDEFINEDVALUE_
#define _UNDEFINEDVALUE_

#include "parser/value/value.h"

namespace lotus {

	class UndefinedValue : public IValue {
	public:

		UndefinedValue();

		int asInt(Module& module) override;
		double asDouble(Module& module) override;
		bool asBool(Module& module) override;
		String asString(Module& module) override;

		Value sizeInRam() override;
	};

}

#endif // _UNDEFINEDVALUE_