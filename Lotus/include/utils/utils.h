#pragma once

#ifndef _UTILS_
#define _UTILS_

#include "utils/lotusTypes.h"
#include <vector>

namespace lotus {

	struct Module;

	Value callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions, Module& module);

	std::wstring wreadContent(const std::wstring& filePath);

	std::pair<Int, Int> evalDayOfYearAndDayOfWeek(Int day, Int month, Int year);

	bool isValidDate(Int day, Int month, Int year);

	int64_t getTotalSeconds(Value time, Module& module);

	std::tuple<Int, Int, Int, Int, Int, Int> fromTotalSeconds(Int total_seconds);

	std::string wstring_to_string(const std::wstring& wstr);

	bool isNumber(const Value& value);

	struct ThrowValue {
		ThrowValue() = default;
		ThrowValue(const Value& value) : value(value) {}
		Value value;
	};
}

#endif // _UTILS_