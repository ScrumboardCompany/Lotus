#pragma once

#ifndef _BLOCKSTATEMENT_
#define _BLOCKSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class BlockStatement : public IStatement {
		std::vector<Statement> statements;
	public:

		BlockStatement(std::vector<Statement> statements);
		void execute() override;
	};

}

#endif // _BLOCKSTATEMENT_