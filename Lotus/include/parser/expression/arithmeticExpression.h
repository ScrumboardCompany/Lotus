#pragma once

#ifndef _ARITHMETICEXPRESSION_
#define _ARITHMETICEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	enum class ArithmeticOperationType {
		ADD,
		SUBSTRACT,
		MULTIPLY,
		DIVIDE,
		POWER,
		MODULE
	};

	class ArithmeticExpression : public IExpression {
		Expression expression1, expression2;

		ArithmeticOperationType operation;

	public:
		ArithmeticExpression(const Expression& expression1, const Expression& expression2, const ArithmeticOperationType& operation);

		Value eval(Module& module) override;
	};
}

#endif // _ARITHMETICEXPRESSION_