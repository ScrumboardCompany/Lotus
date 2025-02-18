#pragma once

#ifndef _BITWISEEXPRESSION_
#define _BITWISEEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

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

		BitwiseOperationType operation;

	public:
		BitwiseExpression(const Expression& expression1, const Expression& expression2, const BitwiseOperationType& operation);

		Value eval() override;
	};
}

#endif // _BITWISEEXPRESSION_