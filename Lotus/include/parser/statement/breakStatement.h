#pragma once

#ifndef _BREAKSTATEMENT_
#define _BREAKSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class BreakStatement : public IStatement {

	public:

		BreakStatement();
		void execute() override;
	};

}

#endif // _BREAKSTATEMENT_