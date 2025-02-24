#pragma once

#ifndef _WHILESTATEMENT_
#define _WHILESTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class WhileStatement : public IStatement {
		std::vector<Expression> conditionPart;
		Statement body;

	public:

		WhileStatement(const std::vector<Expression>& conditionPart, const Statement& body);
		void execute(Module& module) override;
	};


}

#endif // _WHILESTATEMENT_