#pragma once

#ifndef _INDEXEXPRESSION_
#define _INDEXEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;

	class IndexExpression : public IExpression {
		Expression expression;
		Expression index;
		Variables& variables;

		friend class SetExpression;

	public:
		IndexExpression(const Expression& expression, const Expression& index, Variables& variables);

		Value eval() override;
	};
}

#endif // _INDEXEXPRESSION_
