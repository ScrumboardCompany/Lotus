#pragma once

#ifndef _SETEXPRESSION_
#define _SETEXPRESSION_

#include "parser/expression/expresion.h"
#include "structures/variables.h"

namespace lotus {

	enum class SetOperationType {
		SET,
		ADDSET,
		SUBSTRACTSET,
		MULTIPLYSET,
		DIVIDESET
	};

	class SetExpression : public IExpression {

		Expression expression1;
		Expression expression2;

		SetOperationType operation;

	public:
		SetExpression(const Expression& expression1, const Expression& expression2, const SetOperationType& operation);

		Value eval() override;
	};
}

#endif // _SETEXPRESSION_
