#pragma once

#ifndef _PRINTSTATEMENT_
#define _PRINTSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

#include <vector>

namespace lotus {

	class PrintStatement : public IStatement {
		Expression arg;
	public:

		PrintStatement(Expression arg);
		void execute() override;
	};

}

#endif // _PRINTSTATEMENT_