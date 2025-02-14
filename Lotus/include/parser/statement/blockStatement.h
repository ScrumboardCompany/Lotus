#pragma once

#ifndef _BLOCKSTATEMENT_
#define _BLOCKSTATEMENT_
#include "parser/statement/statement.h"

namespace lotus {

	class BlockStatement : public IStatement {
		std::vector<Statement> statements;
	public:

		BlockStatement(const std::vector<Statement>& statements);
		void execute() override;
	};

}

#endif // _BLOCKSTATEMENT_