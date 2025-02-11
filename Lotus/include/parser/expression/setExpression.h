#pragma once

#ifndef _SETEXPRESSION_
#define _SETEXPRESSION_

#include "parser/expression/expresion.h"
#include "structures/variables.h"

namespace lotus {

	class SetExpression : public IExpression {

		Expression expression1;
		Expression expression2;

	public:
		SetExpression(const Expression& expression1, const Expression& expression2);

		Value eval() override;
	};
}

#endif // _SETEXPRESSION_
