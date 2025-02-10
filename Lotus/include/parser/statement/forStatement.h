#pragma once

#ifndef _FORSTATEMENT_
#define _FORSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class ForStatement : public IStatement {
		std::vector<Expression> declaringPart;
		std::vector<Expression> conditionPart;
		std::vector<Expression> actionPart;

		Statement body;

	public:

		ForStatement(std::vector<Expression> declaringPart,	std::vector<Expression> conditionPart, std::vector<Expression> actionPart, Statement body);
		void execute() override;
	};

}

#endif // _PRINTSTATEMENT_