#pragma once

#ifndef _CLASS_
#define _CLASS_

#include "structures/static.h"

namespace lotus {

	class Classes;
	class Functions;

	struct LOTUS_API Class : public Static {

		Class() = default;

		void setName(const String& name);
		void setName(const char* name);

	private:
		friend class ClassStatement;
		friend class Classes;

		void registerClass(Module& module);
		Function makeDefaultConstructor();
	};
}

#endif // _CLASS_