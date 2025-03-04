#pragma once

#ifndef _LAMBDAEXPRESSION_
#define _LAMBDAEXPRESSION_

#include "parser/expression/expression.h"
#include "parser/function/function.h"

namespace lotus {

	class LambdaExpression : public IExpression {
		Function function;

	public:
		LambdaExpression(const Function& function);

		Value eval(Module&) override;
	};
}

#endif // _LAMBDAEXPRESSION_
