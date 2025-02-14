#pragma once

#ifndef _INDEXEXPRESSION_
#define _INDEXEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class IndexExpression : public IExpression {
		Expression expression;
		Expression index;

		friend class SetExpression;

	public:
		IndexExpression(const Expression& expression, const Expression& index);

		Value eval() override;
	};
}

#endif // _INDEXEXPRESSION_
