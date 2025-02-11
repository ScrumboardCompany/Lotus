#pragma once

#ifndef _CONTINUESTATEMENT_
#define _CONTINUESTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class ContinueStatement : public IStatement {

	public:

		ContinueStatement();
		void execute() override;
	};

}

#endif // _CONTINUESTATEMENT_