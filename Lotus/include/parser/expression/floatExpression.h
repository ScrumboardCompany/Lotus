#pragma once

#ifndef _FLOATEXPRESSION_
#define _FLOATEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class FloatExpression : public IExpression {
		double value;

	public:
		FloatExpression(double value);

		Value eval(Module&) override;
	};
}

#endif // _FLOATEXPRESSION_
