#pragma once

#ifndef _IMPORTSTATEMENT_
#define _IMPORTSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	struct Module;
	class Parser;

	enum class KeyType {
		VARIABLE,
		FUNCTION,
		STATIC,
		CLASS,
		ENUM,
		UNKNOWN,
		NOTYPE
	};

	struct ImportElementInfo {
		String key;
		KeyType type = KeyType::UNKNOWN;
		String stringType;
	};

	class ImportStatement : public IStatement {

		std::vector<ImportElementInfo> elements;
		String filePath;
		StringMap<Module>& modules;

		void loadFromModule(Module& from, Module& to);

	public:

		ImportStatement(const std::vector<ImportElementInfo>& elements, const String& filePath, StringMap<Module>& modules);
		void execute(Module& currentModule) override;
	};

}

#endif // _IMPORTSTATEMENT_