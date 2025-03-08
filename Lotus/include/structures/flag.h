#pragma once

#ifndef _FLAG_
#define _FLAG_

namespace lotus {

	struct Flag {
		bool value;
		bool defaultValue;

		Flag() = default;
		Flag(bool value, bool defaultValue) : value(value), defaultValue(defaultValue) {}
	};
}
#endif // _FLAG_