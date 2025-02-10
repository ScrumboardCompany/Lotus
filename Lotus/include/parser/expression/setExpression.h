#pragma once

#ifndef _SETEXPRESSION_
#define _SETEXPRESSION_

#include "parser/expression/expresion.h"
#include "structures/variables.h"

namespace lotus {

	class SetExpression : public IExpression {

		String name;
		Expression expression;
		Variables& variables;

	public:
		SetExpression(const String& name, Expression expression, Variables& variables);

		Value eval() override;
	};
}

#endif // _SETEXPRESSION_
