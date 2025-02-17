#pragma once

#ifndef _CALLLAMBDAEXPRESSION_
#define _CALLLAMBDAEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	class CallLambdaExpression : public IExpression {
		Variables& variables;
		std::vector<Expression> args;
		Expression function;

	public:
		CallLambdaExpression(Variables& variables, const std::vector<Expression>& args, const Expression& function);

		Value eval() override;
	};
}

#endif // _CALLLAMBDAEXPRESSION_
