#pragma once

#ifndef _VARIABLEEXPRESSION_
#define _VARIABLEEXPRESSION_

#include "parser/expression/expresion.h"
#include "structures/variables.h"

namespace lotus {

	class VariableExpression : public IExpression {
		String name;
		Variables& variables;

	public:
		VariableExpression(const String& name, Variables& variables);

		Value eval() override;
	};
}

#endif // _VARIABLEEXPRESSION_