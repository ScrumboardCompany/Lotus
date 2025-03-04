#pragma once

#ifndef _BITWISEEXPRESSION_
#define _BITWISEEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class Variables;

	enum class BitwiseOperationType {
		AND,
		OR,
		XOR,
		LEFTSHIFT,
		RIGHTSHIFT
	};

	class BitwiseExpression : public IExpression {
		Expression expression1, expression2;

		BitwiseOperationType operation;

	public:
		BitwiseExpression(const Expression& expression1, const Expression& expression2, const BitwiseOperationType& operation);

		Value eval(Module& module) override;
	};
}

#endif // _BITWISEEXPRESSION_