#include "parser/expression/staticFieldExpression.h"
#include "structures/statics.h"

using namespace lotus;

lotus::StaticFieldExpression::StaticFieldExpression(const String& staticName, const String& field, Statics& statics)
	: staticName(staticName), field(field), statics(statics) {}

Value lotus::StaticFieldExpression::eval() {
	return statics.get(staticName).getField(field);
}
