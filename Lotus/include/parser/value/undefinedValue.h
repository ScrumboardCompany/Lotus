#pragma once

#ifndef _UNDEFINEDVALUE_
#define _UNDEFINEDVALUE_

#include "parser/value/value.h"

namespace lotus {

	class UndefinedValue : public IValue {
	public:

		UndefinedValue() = default;

		int asInt() override;
		double asDouble() override;
		bool asBool() override;
		String asString() override;

		String getType() const override;
	};

}

#endif // _UNDEFINEDVALUE_