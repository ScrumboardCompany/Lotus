#pragma once

#ifndef _IMPORTSTATEMENT_
#define _IMPORTSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Variables;
	class Functions;
	struct Module;
	class Flags;

	class ImportStatement : public IStatement {
		
		String key;
		String filePath;
		Variables& variables;
		Functions& functions;
		StringMap<Module>& modules;
		const Flags& flags;

	public:

		ImportStatement(const String& key, const String& filePath, Variables& variables, Functions& functions, StringMap<Module>& modules, const Flags& flags);
		void execute() override;
	};

}

#endif // _IMPORTSTATEMENT_