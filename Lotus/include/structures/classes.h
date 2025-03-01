#pragma once

#ifndef _CLASSES_
#define _CLASSES_

#include "structures/class.h"
#include "utils/lotusTypes.h"

namespace lotus {
	
	struct Module;

	class Classes {
		StringMap<Ptr<Class>> classes;

		friend class ImportStatement;
	public:
		Classes() = default;

		void forceSet(const String& name, const Ptr<Class>& value);

		void forceSet(const char* name, const Ptr<Class>& value);

		void declare(const String& name, const Ptr<Class>& value);

		void declare(const char* name, const Ptr<Class>& value);

		void set(const String& name, const Ptr<Class>& value);

		void set(const char* name, const Ptr<Class>& value);

		Ptr<Class> get(const String& name);

		Ptr<Class> get(const char* name);

		bool isExists(const String& name);

		bool isExists(const char* name);

		void registerClass(const String& name, Module& module);

		void registerClass(const char* name, Module& module);
	};
}

#endif // _CLASSES_