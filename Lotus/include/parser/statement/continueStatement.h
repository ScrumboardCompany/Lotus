#pragma once

#ifndef _CONTINUESTATEMENT_
#define _CONTINUESTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class ContinueStatement : public IStatement {

	public:

		ContinueStatement();
		void execute(Module&) override;
	};

}

#endif // _CONTINUESTATEMENT_