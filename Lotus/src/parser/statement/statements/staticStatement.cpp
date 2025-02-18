#include "parser/statement/staticStatement.h"
#include "structures/statics.h"

using namespace lotus;

lotus::StaticStatement::StaticStatement(Statics& statics, const String& name, RawFields_t& fields, const Methods_t& methods)
	: statics(statics), name(name), fields(fields), methods(methods) {}

void lotus::StaticStatement::execute() {
	Static value;
	for (auto& field : fields) {

		FieldMemberInfo memberInfo;
		memberInfo.value = field.second.first ? field.second.first->eval() : UNDEFINED();
		memberInfo.accessModifier = field.second.second.accessModifier;

		value.fields.emplace(field.first, memberInfo);
	}

	value.methods = methods;

	statics.declare(name, value);
}