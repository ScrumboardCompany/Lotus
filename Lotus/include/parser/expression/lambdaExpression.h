#pragma once

#ifndef _LAMBDAEXPRESSION_
#define _LAMBDAEXPRESSION_

#include "parser/expression/expresion.h"
#include "parser/function/function.h"

namespace lotus {

	class LambdaExpression : public IExpression {
		Variables& variables;
		Function function;

	public:
		LambdaExpression(Variables& variables, const Function& function);

		Value eval() override;
	};
}

#endif // _LAMBDAEXPRESSION_
