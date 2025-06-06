#pragma once

#ifndef _ENUM_
#define _ENUM_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"

namespace lotus {

	struct Module;

	struct LOTUS_API Enum {

		// You can pass anything module. It's stub
		void addElement(const String& key, Value value, Module& module);

		// You can pass anything module. It's stub
		void addElement(const char* key, const Value& value, Module& module);

		Value& getElement(const String& key);

		Value& getElement(const char* key);

		bool isExists(const String& key);

		bool isExists(const char* key);

	private:
		StringMap<Value> elements;
	};
}

#endif // _ENUM_