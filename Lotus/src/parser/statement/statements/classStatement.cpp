#include "parser/statement/classStatement.h"
#include "parser/value/classValue.h"
#include "structures/module.h"

using namespace lotus;

lotus::ClassStatement::ClassStatement(const String& name, RawFields_t& fields, const Methods_t& methods, const std::vector<String>& parents)
	: name(name), fields(fields), methods(methods), parents(parents) {
}

void lotus::ClassStatement::execute(Module& module) {
	Ptr<Class> newClass = MAKE_PTR<Class>();

	for (auto& field : fields) {

		FieldMemberInfo memberInfo;
		memberInfo.value = field.second.first->eval(module);
		memberInfo.accessModifier = field.second.second.accessModifier;

		newClass->addField(field.first, memberInfo);
	}

	for (auto& method : methods) {
		for (size_t i = 0; i < method.second.size(); i++) {
			newClass->addMethod(method.first, method.second[i]);
		}
	}
	newClass->setName(name);

	std::vector<ClassValue> parentClasses;
	for (auto& parent : parents) {
		newClass->value.parents.push_back(MAKE_PTR<ClassValue>(module.classes.get(parent)->value));
	}

	module.classes.declare(name, newClass);
	module.classes.registerClass(name, module);
}