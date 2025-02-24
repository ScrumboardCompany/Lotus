#pragma once

#ifndef _UNARYEXPRESSION_
#define _UNARYEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	enum class UnaryOperationType {
		PLUS,
		MINUS,
		LOGICALNOT,
		BITWISENOT,
		PREFIXINCREMENT,
		POSTFIXINCREMENT,
		PREFIXDECREMENT,
		POSTFIXDECREMENT
	};

	class UnaryExpression : public IExpression {
		Expression expression;

		UnaryOperationType operation;

	public:
		UnaryExpression(const Expression& expression, const UnaryOperationType& operation);

		Value eval(Module& module) override;
	};
}

#endif // _UNARYEXPRESSION_