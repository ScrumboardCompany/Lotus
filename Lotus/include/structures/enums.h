#pragma once

#ifndef _ENUMS_
#define _ENUMS_

#include "structures/enum.h"

namespace lotus {

	class Enums {
		StringMap<Enum> enums;
		friend class ImportStatement;

	public:

		void forceSet(const String& name, const Enum& value);

		void forceSet(const char* name, const Enum& value);

		void declare(const String& name, const Enum& value);

		void declare(const char* name, const Enum& value);

		void set(const String& name, const Enum& value);

		void set(const char* name, const Enum& value);

		Enum& get(const String& name);

		Enum& get(const char* name);

		bool isExists(const String& name);

		bool isExists(const char* name);
	};
}

#endif // _ENUMS_