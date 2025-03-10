#include "parser/expression/staticFieldOrEnumExpression.h"
#include "structures/module.h"
#include "utils/lotusError.h"
#include "parser/value/enumValue.h"

using namespace lotus;

lotus::StaticFieldOrEnumExpression::StaticFieldOrEnumExpression(const String& staticName, const String& field)
	: staticName(staticName), field(field) {}

Value lotus::StaticFieldOrEnumExpression::eval(Module& module) {
	if (module.statics.isExists(staticName)) {
		return module.statics.get(staticName).getField(field);
	}
	else if (module.enums.isExists(staticName)) {
		return MAKE_PTR<EnumValue>(module.enums.get(staticName).getElement(field), staticName);
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined enum or static with name \"") + staticName + STRING_LITERAL("\""));
	}
}
