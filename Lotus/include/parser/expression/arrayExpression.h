#pragma once

#ifndef _ARRAYEXPRESSION_
#define _ARRAYEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class ArrayExpression : public IExpression {
		std::vector<Expression> elements;

	public:
		ArrayExpression(const std::vector<Expression>& elements);

		Value eval(Module& module) override;
	};
}

#endif // _ARRAYEXPRESSION_
