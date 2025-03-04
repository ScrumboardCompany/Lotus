#pragma once

#ifndef _LETEXPRESSION_
#define _LETEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class Variables;

	class LetExpression : public IExpression {

		String name;
		Expression expression;

	public:
		LetExpression(const String& name, const Expression& expression);

		Value eval(Module& module) override;
	};
}

#endif // _LETEXPRESSION_
