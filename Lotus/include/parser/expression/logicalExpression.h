#pragma once

#ifndef _LOGICALEXPRESSION_
#define _LOGICALEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class Variables;

	enum class LogicalOperationType {
		GREATER,
		LESS,
		GREATEREQUAL,
		LESSEQUAL,
		EQUALITY,
		INEQUALITY,
		OR,
		AND
	};

	class LogicalExpression : public IExpression {
		Expression expression1, expression2;

		LogicalOperationType operation;

	public:
		LogicalExpression(const Expression& expression1, const Expression& expression2, const LogicalOperationType& operation);

		Value eval(Module& module) override;
	};
}

#endif // _LOGICALEXPRESSION_