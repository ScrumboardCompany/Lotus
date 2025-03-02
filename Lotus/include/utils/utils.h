#pragma once

#ifndef _UTILS_
#define _UTILS_

#include "utils/lotusTypes.h"
#include <vector>

namespace lotus {

	struct Module;

	Value callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions, Module& module);

	std::wstring wreadContent(const std::wstring& filePath);

	std::pair<int, int> evalDayOfYearAndDayOfWeek(int sec, int min, int hour, int day, int month, int year);

	errno_t localtime(tm* _Tm, const time_t* _Time);

	bool isValidDate(int day, int month, int year);

	int64_t getTotalSeconds(Value time, Module& module);

	std::tuple<int, int, int, int, int, int> fromTotalSeconds(int64_t total_seconds);

	struct ThrowValue {
		ThrowValue() = default;
		ThrowValue(const Value& value) : value(value) {}
		Value value;
	};
}

#endif // _UTILS_