#pragma once

#ifndef _STATICS_
#define _STATICS_

#include "structures/static.h"

namespace lotus {

	class Statics {
		StringMap<Static> statics;
		friend class ImportStatement;

	public:

		void forceSet(const String& name, const Static& value);

		void forceSet(const char* name, const Static& value);

		void declare(const String& name, const Static& value);

		void declare(const char* name, const Static& value);

		void set(const String& name, const Static& value);

		void set(const char* name, const Static& value);

		Static& get(const String& name);

		Static& get(const char* name);

		bool isExists(const String& name);

		bool isExists(const char* name);
	};

}

#endif // _STATICS_