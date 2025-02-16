#pragma once

#ifndef _SWITCHCASESTATEMENT_
#define _SWITCHCASESTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Variables;

	class SwitchCaseStatement : public IStatement {
		Expression exprToCheck;
		std::vector<std::pair<Expression, Statement>> cases;
		Statement defaultBody;

		Variables& variables;

	public:

		SwitchCaseStatement(const Expression& exprToCheck, const std::vector<std::pair<Expression, Statement>>& cases, const Statement& defaultBody, Variables& variables);
		void execute() override;
	};

}

#endif // _SWITCHCASESTATEMENT_