#pragma once

#ifndef _INTEXPRESSION_
#define _INTEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class IntExpression : public IExpression {
		Int value;

	public:
		IntExpression(Int value);

		Value eval(Module&) override;
	};
}

#endif // _INTEXPRESSION_
