#pragma once

#ifndef _FORSTATEMENT_
#define _FORSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Variables;

	class ForStatement : public IStatement {
		std::vector<Expression> declaringPart;
		std::vector<Expression> conditionPart;
		std::vector<Expression> actionPart;

		Statement body;

		Variables& variables;

	public:

		ForStatement(const std::vector<Expression>& declaringPart, const std::vector<Expression>& conditionPart, const std::vector<Expression>& actionPart, const Statement& body, Variables& variables);
		void execute() override;
	};

}

#endif // _FORSTATEMENT_