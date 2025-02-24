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

	public:

		SwitchCaseStatement(const Expression& exprToCheck, const std::vector<std::pair<Expression, Statement>>& cases, const Statement& defaultBody);
		void execute(Module& module) override;
	};

}

#endif // _SWITCHCASESTATEMENT_