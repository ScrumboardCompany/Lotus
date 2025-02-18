#pragma once

#ifndef _STATICFIELDEXPRESSION_
#define _STATICFIELDEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Statics;

	class StaticFieldExpression : public IExpression {

		String staticName;
		String field;
		Statics& statics;

		friend class SetExpression;

	public:
		StaticFieldExpression(const String& staticName, const String& field, Statics& statics);

		Value eval() override;
	};
}

#endif // _STATICFIELDEXPRESSION_
