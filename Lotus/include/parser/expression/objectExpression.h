#pragma once

#ifndef _OBJECTEXPRESSION_
#define _OBJECTEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	class ObjectExpression : public IExpression {

		StringMap<Expression> fields;

	public:
		ObjectExpression(const StringMap<Expression>& fields);

		Value eval() override;
	};
}

#endif // _OBJECTEXPRESSION_
