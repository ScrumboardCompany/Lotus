#pragma once

#ifndef _SWAPEXPRESSION_
#define _SWAPEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class SwapExpression : public IExpression {

		Expression expr1;
		Expression expr2;

	public:
		SwapExpression(const Expression& expr1, const Expression& expr2);

		Value eval(Module& module) override;
	};
}

#endif // _SWAPEXPRESSION_