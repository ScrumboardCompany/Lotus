#pragma once

#ifndef _CALLLAMBDAEXPRESSION_
#define _CALLLAMBDAEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	class CallLambdaExpression : public IExpression {
		std::vector<Expression> args;
		Expression function;

	public:
		CallLambdaExpression(const std::vector<Expression>& args, const Expression& function);

		Value eval(Module& module) override;
	};
}

#endif // _CALLLAMBDAEXPRESSION_
