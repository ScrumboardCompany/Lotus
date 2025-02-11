#pragma once

#ifndef _LETEXPRESSION_
#define _LETEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	class LetExpression : public IExpression {

		String name;
		Expression expression;
		Variables& variables;

	public:
		LetExpression(const String& name, Expression expression, Variables& variables);

		Value eval() override;
	};
}

#endif // _LETEXPRESSION_
