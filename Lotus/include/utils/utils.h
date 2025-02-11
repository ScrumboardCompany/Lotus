#pragma once

#ifndef _UTILS_
#define _UTILS_

#include "utils/lotusTypes.h"
#include <vector>

namespace lotus {

	Value callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions);

	std::wstring wreadContent(const std::wstring& filePath);
}

#endif // _UTILS_