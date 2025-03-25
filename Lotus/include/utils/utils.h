#pragma once

#ifndef _UTILS_
#define _UTILS_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include <vector>

namespace lotus {

	struct Module;

	class Parser;

	LOTUS_API Value callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions, Module& module);

	LOTUS_API void setConsoleLocale();

	LOTUS_API std::wstring wreadContent(const std::wstring& filePath);

	LOTUS_API std::pair<Int, Int> evalDayOfYearAndDayOfWeek(Int day, Int month, Int year);

	LOTUS_API bool isValidDate(Int day, Int month, Int year);

	LOTUS_API int64_t getTotalSeconds(Value time, Module& module);

	LOTUS_API std::tuple<Int, Int, Int, Int, Int, Int> fromTotalSeconds(Int total_seconds, bool absolute);

	LOTUS_API std::wstring string_to_wstring_codecvt(const std::string& str);

	LOTUS_API std::string wstring_to_string_codecvt(const std::wstring& wstr);

	LOTUS_API std::string wstring_to_string(const std::wstring& wstr);

	LOTUS_API void nowTime(tm* _Tm);

	LOTUS_API String nowTimeInString();

	LOTUS_API double Cstod(const String& str);

	class LOTUS_API Compiler {
		static std::vector<Ptr<Parser>> parsers;

	public:
		static Module& compile(const String& filePath, const StringMap<bool>& flags);
	};

	LOTUS_API bool isNumber(const Value& value);

	struct LOTUS_API ThrowValue {
		ThrowValue() = default;
		ThrowValue(const Value& value) : value(value) {}
		Value value;
	};
}

#endif // _UTILS_