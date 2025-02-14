#pragma once

#ifndef _STRUCTVALUE_
#define _STRUCTVALUE_

#include "parser/value/value.h"

namespace lotus {

	class StructValue : public IValue {
	public:

		StructValue() = default;

		Value sizeInRam() override;
	};

}

#endif // _STRUCTVALUE_