#pragma once

#ifndef _FLAGSTATEMENT_
#define _FLAGSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Flags;

	class FlagStatement : public IStatement {

		String flag;
		bool value;
		Flags& flags;

	public:

		FlagStatement(const String& flag, bool value, Flags& flags);
		void execute() override;
	};

}

#endif // _FLAGSTATEMENT_