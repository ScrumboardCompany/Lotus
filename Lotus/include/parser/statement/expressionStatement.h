#pragma once

#ifndef _EXPRESSIONSTATEMENT_
#define _EXPRESSIONSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class ExpressionStatement : public IStatement {
		Expression expression;
	public:

		ExpressionStatement(Expression expression);
		void execute() override;
	};

}

#endif // _EXPRESSIONSTATEMENT_