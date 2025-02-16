#pragma once

#ifndef _CLASSVALUE_
#define _CLASSVALUE_

#include "parser/value/value.h"
#include "parser/function/function.h"

namespace lotus {

	class ClassValue : public IValue {
	public:

		ClassValue() = default;

		Value sizeInRam() override;
	};

}

#endif // _CLASSVALUE_