#pragma once

#ifndef _FUNCTIONEXPRESSION_
#define _FUNCTIONEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Functions;
	class Variables;

	class FunctionExpression : public IExpression {
		String name;
		Functions& functions;
		Variables& variables;
		std::vector<Expression> args;

	public:
		FunctionExpression(const String& name, Functions& functions, Variables& variables, const std::vector<Expression>& args);

		Value eval() override;
	};
}

#endif // _FUNCTIONEXPRESSION_
