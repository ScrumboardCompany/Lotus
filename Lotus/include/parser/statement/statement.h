#pragma once

#ifndef _STATEMENT_
#define _STATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/expression/expresion.h"

namespace lotus {

	class IStatement {
	public:
		virtual void execute() = 0;
		virtual ~IStatement() = default;
	};

}

#endif // _STATEMENT_