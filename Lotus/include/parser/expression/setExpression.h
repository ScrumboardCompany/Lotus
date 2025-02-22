#pragma once

#ifndef _SETEXPRESSION_
#define _SETEXPRESSION_

#include "parser/expression/expresion.h"
#include "structures/variables.h"

namespace lotus {

	class Variables;

	enum class SetOperationType {
		SET,
		ADDSET,
		SUBSTRACTSET,
		MULTIPLYSET,
		DIVIDESET,
		POWERSET,
		DIVIDEMODULESET,
		BITWISEANDSET,
		BITWISEORSET,
		BITWISEXORSET,
		BITWISENOTSET,
		BITWISELEFTSHIFTSET,
		BITIWSERIGHTSHIFTSET
	};

	class SetExpression : public IExpression {

		Expression expression1;
		Expression expression2;
		Variables& variables;

		SetOperationType operation;

	public:
		SetExpression(const Expression& expression1, const Expression& expression2, const SetOperationType& operation, Variables& variables);

		Value eval() override;
	};
}

#endif // _SETEXPRESSION_
