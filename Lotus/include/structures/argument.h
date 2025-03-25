#pragma once

#ifndef _ARGUMENT_
#define _ARGUMENT_

#include "utils/lotusTypes.h"

namespace lotus {

	struct LOTUS_API Argument {
		String name;
		bool isVariadic;

		Argument(const String& name, bool isVariadic = false) : name(name), isVariadic(isVariadic) {}
	};
}

#endif // _ARGUMENT_