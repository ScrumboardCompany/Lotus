#pragma once

#ifndef _ARRAYEXPRESSION_
#define _ARRAYEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class ArrayExpression : public IExpression {
		std::vector<Expression> elements;

	public:
		ArrayExpression(std::vector<Expression> elements);

		Value eval() override;
	};
}

#endif // _ARRAYEXPRESSION_
