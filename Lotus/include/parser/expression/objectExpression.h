#pragma once

#ifndef _OBJECTEXPRESSION_
#define _OBJECTEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class Variables;

	class ObjectExpression : public IExpression {
		StringMap<Expression> fields;

	public:
		ObjectExpression(const StringMap<Expression>& fields);

		Value eval(Module& module) override;
	};
}

#endif // _OBJECTEXPRESSION_
