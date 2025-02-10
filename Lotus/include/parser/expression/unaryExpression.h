#pragma once

#ifndef _UNARYEXPRESSION_
#define _UNARYEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	enum class UnaryOperationType {
		PLUS,
		MINUS,
		NOT
	};

	class UnaryExpression : public IExpression {
		Expression expression;

		UnaryOperationType operation;

	public:
		UnaryExpression(const Expression& expression, const UnaryOperationType& operation);

		Value eval() override;
	};
}

#endif // _UNARYEXPRESSION_