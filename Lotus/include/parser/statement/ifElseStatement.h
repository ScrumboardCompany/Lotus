#pragma once

#ifndef _IFELSESTATEMENT_
#define _IFELSESTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Variables;

	class IfElseStatement : public IStatement {
		std::vector<Expression> conditionPart;
		Statement ifBody;
		Statement elseBody;

	public:

		IfElseStatement(const std::vector<Expression>& conditionPart, const Statement& ifBody, const Statement& elseBody);
		void execute(Module& module) override;
	};

}

#endif // _IFELSESTATEMENT_