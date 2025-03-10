#include "parser/statement/enumStatement.h"
#include "structures/module.h"

using namespace lotus;

lotus::EnumStatement::EnumStatement(const String& name, const StringMap<Expression>& elements)
	: name(name), elements(elements) {}

void lotus::EnumStatement::execute(Module& module) {
	Enum enum_;

	for (auto& element : elements) {
		enum_.addElement(element.first, element.second->eval(module), module);
	}

	module.ENUM(name, enum_);
}