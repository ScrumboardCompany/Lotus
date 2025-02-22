#include "parser/statement/classStatement.h"
#include "parser/value/classValue.h"
#include "structures/functions.h"
#include "structures/variables.h"
#include "structures/class.h"
#include "structures/classes.h"

using namespace lotus;

lotus::ClassStatement::ClassStatement(Classes& classes, Functions& functions, Variables& variables, const String& name, RawFields_t& fields, const Methods_t& methods, const std::vector<String>& parents)
	: classes(classes), functions(functions), variables(variables), name(name), fields(fields), methods(methods), parents(parents) {
}

void lotus::ClassStatement::execute() {
	Ptr<Class> newClass = MAKE_PTR<Class>();

	for (auto& field : fields) {

		FieldMemberInfo memberInfo;
		memberInfo.value = field.second.first ? field.second.first->eval() : UNDEFINED();
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
		newClass->value.parents.push_back(MAKE_PTR<ClassValue>(classes.get(parent)->value));		
	}

	classes.declare(name, newClass);
	classes.registerClass(name, functions, variables);
}