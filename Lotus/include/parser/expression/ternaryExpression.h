#pragma once

#ifndef _TERNARYEXPRESSION_
#define _TERNARYEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class Variables;

	class TernaryExpression : public IExpression {

		Expression condition;
		Expression expr1;
		Expression expr2;

	public:
		TernaryExpression(const Expression& condition, const Expression& expr1, const Expression& expr2);

		Value eval(Module& module) override;
	};
}

#endif // _TERNARYEXPRESSION_
