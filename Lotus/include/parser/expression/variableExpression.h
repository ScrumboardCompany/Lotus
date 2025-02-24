#pragma once

#ifndef _VARIABLEEXPRESSION_
#define _VARIABLEEXPRESSION_

#include "parser/expression/expresion.h"
#include "structures/variables.h"

namespace lotus {

	class VariableExpression : public IExpression {
		String name;

		friend class SetExpression;

	public:
		VariableExpression(const String& name);

		Value eval(Module& module) override;
	};
}

#endif // _VARIABLEEXPRESSION_