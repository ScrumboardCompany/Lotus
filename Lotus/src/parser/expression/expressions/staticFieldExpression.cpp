#include "parser/expression/staticFieldExpression.h"
#include "structures/module.h"

using namespace lotus;

lotus::StaticFieldExpression::StaticFieldExpression(const String& staticName, const String& field)
	: staticName(staticName), field(field) {}

Value lotus::StaticFieldExpression::eval(Module& module) {
	return module.statics.get(staticName).getField(field);
}
