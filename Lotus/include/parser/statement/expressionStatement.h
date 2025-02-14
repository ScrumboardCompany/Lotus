#pragma once

#ifndef _EXPRESSIONSTATEMENT_
#define _EXPRESSIONSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class ExpressionStatement : public IStatement {
		Expression expression;
	public:

		ExpressionStatement(const Expression& expression);
		void execute() override;
	};

}

#endif // _EXPRESSIONSTATEMENT_