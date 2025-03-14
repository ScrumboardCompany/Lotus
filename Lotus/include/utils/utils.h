#pragma once

#ifndef _UTILS_
#define _UTILS_

#include "utils/lotusTypes.h"
#include <vector>

namespace lotus {

	struct Module;

	class Parser;

	Value callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions, Module& module);

	void setConsoleLocale();

	std::wstring wreadContent(const std::wstring& filePath);

	std::pair<Int, Int> evalDayOfYearAndDayOfWeek(Int day, Int month, Int year);

	bool isValidDate(Int day, Int month, Int year);

	int64_t getTotalSeconds(Value time, Module& module);

	std::tuple<Int, Int, Int, Int, Int, Int> fromTotalSeconds(Int total_seconds);

	std::wstring string_to_wstring_codecvt(const std::string& str);

	std::string wstring_to_string_codecvt(const std::wstring& wstr);

	std::string wstring_to_string(const std::wstring& wstr);

	void nowTime(tm* _Tm);

	String nowTimeInString();

	double Cstod(const String& str);

	class Compiler {
		static std::vector<Ptr<Parser>> parsers;

	public:
		static Module& compile(const String& filePath, const StringMap<bool>& flags);
	};

	bool isNumber(const Value& value);

	struct ThrowValue {
		ThrowValue() = default;
		ThrowValue(const Value& value) : value(value) {}
		Value value;
	};
}

#endif // _UTILS_