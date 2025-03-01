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

	struct ThrowValue {
		ThrowValue() = default;
		ThrowValue(const Value& value) : value(value) {}
		Value value;
	};
}

#endif // _UTILS_