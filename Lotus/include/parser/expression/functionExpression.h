#pragma once

#ifndef _FUNCTIONEXPRESSION_
#define _FUNCTIONEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Functions;

	class FunctionExpression : public IExpression {
		String name;
		Functions& functions;
		std::vector<Expression> args;

	public:
		FunctionExpression(const String& name, Functions& functions, std::vector<Expression> args);

		Value eval() override;
	};
}

#endif // _FUNCTIONEXPRESSION_
