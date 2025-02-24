#pragma once

#ifndef _WORDEXPRESSION_
#define _WORDEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class WordExpression : public IExpression {
		String name;

		friend class SetExpression;

	public:
		WordExpression(const String& name);

		Value eval(Module& module) override;
	};
}

#endif // _WORDEXPRESSION_