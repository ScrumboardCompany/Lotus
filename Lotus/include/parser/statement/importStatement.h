#pragma once

#ifndef _IMPORTSTATEMENT_
#define _IMPORTSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Variables;
	class Flags;

	class ImportStatement : public IStatement {
		
		String key;
		String filePath;
		Variables& variables;
		const Flags& flags;

	public:

		ImportStatement(const String& key, const String& filePath, Variables& variables, const Flags& flags);
		void execute() override;
	};

}

#endif // _IMPORTSTATEMENT_