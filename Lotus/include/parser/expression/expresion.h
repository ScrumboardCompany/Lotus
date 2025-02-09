#pragma once

#ifndef _EXPRESSION_
#define _EXPRESSION_

#include "utils/lotusTypes.h"
#include "parser/value/value.h"

namespace lotus {

	class IExpression {
	public:
		virtual Value eval() = 0;

		virtual ~IExpression() = default;
	};
}

#endif // _EXPRESSION_