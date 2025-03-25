#pragma once

#ifndef _FLAG_
#define _FLAG_

#include "utils/lotusDefines.h"

namespace lotus {

	struct LOTUS_API Flag {
		bool value;
		bool defaultValue;

		Flag() = default;
		Flag(bool value, bool defaultValue) : value(value), defaultValue(defaultValue) {}
	};
}
#endif // _FLAG_