#pragma once

#ifndef _FLOATEXPRESSION_
#define _FLOATEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class FloatExpression : public IExpression {
		double value;

	public:
		FloatExpression(double value);

		Value eval() override;
	};
}

#endif // _FLOATEXPRESSION_
