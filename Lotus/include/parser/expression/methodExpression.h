#pragma once

#ifndef _METHODEXPRESSION_
#define _METHODEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	class MethodExpression : public IExpression {

		Expression expr;
		String method;
		std::vector<Expression> args;
		Variables& variables;

	public:
		MethodExpression(const Expression& expr, const String& method, const std::vector<Expression>& args, Variables& variables);

		Value eval() override;
	};
}

#endif // _METHODEXPRESSION_
