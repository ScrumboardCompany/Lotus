#pragma once

#ifndef _UNDEFINEDEXPRESSION_
#define _UNDEFINEDEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class UndefinedExpression : public IExpression {
	public:
		UndefinedExpression() = default;

		Value eval(Module&) override;
	};
}

#endif // _UNDEFINEDEXPRESSION_
