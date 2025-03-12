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

	std::pair<int, int> evalDayOfYearAndDayOfWeek(int day, int month, int year);

	bool isValidDate(int day, int month, int year);

	int64_t getTotalSeconds(Value time, Module& module);

	std::tuple<int, int, int, int, int, int> fromTotalSeconds(int64_t total_seconds);

	std::string wstring_to_string(const std::wstring& wstr);

	void nowTime(tm* _Tm);

	String nowTimeInString();

	class Compiler {
		static std::vector<Ptr<Parser>> parsers;

	public:
		static Module& compile(const String& filePath, const StringMap<bool>& flags);
	};

	struct ThrowValue {
		ThrowValue() = default;
		ThrowValue(const Value& value) : value(value) {}
		Value value;
	};
}

#endif // _UTILS_