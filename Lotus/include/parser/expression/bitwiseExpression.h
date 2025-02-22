#pragma once

#ifndef _BITWISEEXPRESSION_
#define _BITWISEEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	enum class BitwiseOperationType {
		AND,
		OR,
		XOR,
		NOT,
		LEFTSHIFT,
		RIGHTSHIFT
	};

	class BitwiseExpression : public IExpression {
		Expression expression1, expression2;
		Variables& variables;

		BitwiseOperationType operation;

	public:
		BitwiseExpression(const Expression& expression1, const Expression& expression2, const BitwiseOperationType& operation, Variables& variables);

		Value eval() override;
	};
}

#endif // _BITWISEEXPRESSION_