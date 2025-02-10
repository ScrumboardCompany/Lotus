#pragma once

#ifndef _WHILESTATEMENT_
#define _WHILESTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class WhileStatement : public IStatement {
		std::vector<Expression> conditionPart;
		Statement body;
	public:

		WhileStatement(std::vector<Expression> conditionPart, Statement body);
		void execute() override;
	};

}

#endif // _WHILESTATEMENT_