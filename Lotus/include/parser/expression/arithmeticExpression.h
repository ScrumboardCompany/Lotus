#pragma once

#ifndef _ARITHMETICEXPRESSION_
#define _ARITHMETICEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	enum class ArithmeticOperationType {
		ADD,
		SUBSTRACT,
		MULTIPLY,
		DIVIDE
	};

	class ArithmeticExpression : public IExpression {
		Expression expression1, expression2;

		ArithmeticOperationType operation;

	public:
		ArithmeticExpression(const Expression& expression1, const Expression& expression2, const ArithmeticOperationType& operation);

		Value eval() override;
	};
}

#endif // _ARITHMETICEXPRESSION_