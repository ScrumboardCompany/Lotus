#pragma once

#ifndef _IMPORTSTATEMENT_
#define _IMPORTSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	struct Module;
	class Flags;
	class Parser;

	class ImportStatement : public IStatement {
		
		String key;
		String filePath;
		StringMap<Module>& modules;
		const Flags& flags;

		Ptr<Parser> parser;

	public:

		ImportStatement(const String& key, const String& filePath, StringMap<Module>& modules, const Flags& flags);
		void execute(Module& currentModule) override;
	};

}

#endif // _IMPORTSTATEMENT_