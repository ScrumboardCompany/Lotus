#pragma once

#ifndef _FUNCTIONEXPRESSION_
#define _FUNCTIONEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Functions;
	class Variables;

	class FunctionExpression : public IExpression {
		String name;
		std::vector<Expression> args;

	public:
		FunctionExpression(const String& name, const std::vector<Expression>& args);

		Value eval(Module& module) override;
	};
}

#endif // _FUNCTIONEXPRESSION_
