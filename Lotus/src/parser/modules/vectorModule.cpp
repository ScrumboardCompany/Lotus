#include "parser/parser.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/stringValue.h"
#include "utils/lotusError.h"
#include "utils/utils.h"

using namespace lotus;

void lotus::Parser::loadVectorModule() {
	static Module Vector;

	Class Vector2Class;

	Vector2Class.addField("X", FIELD(AccessModifierType::PRIVATE, FLOAT(0)));
	Vector2Class.addField("Y", FIELD(AccessModifierType::PRIVATE, FLOAT(0)));

	Vector2Class.addMethod("X", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("X"));
		}));

	Vector2Class.addMethod("X", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!isNumber(module.GET("X"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("X")->getType(), module);
		Value& thisValue = module.GET("this");
		thisValue->getField("X") = FLOAT(module.GET("X")->asDouble(module));
		}, "X"));

	Vector2Class.addMethod("Y", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("Y"));
		}));

	Vector2Class.addMethod("Y", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!isNumber(module.GET("Y"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("Y")->getType(), module);
		Value& thisValue = module.GET("this");
		thisValue->getField("Y") = FLOAT(module.GET("Y")->asDouble(module));
		}, "Y"));

	Vector2Class.addMethod("Vector2", METHOD(AccessModifierType::PUBLIC, [&] {}));

	Vector2Class.addMethod("Vector2", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		
		if (!isNumber(module.GET("X"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("X")->getType(), module);
		if (!isNumber(module.GET("Y"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("Y")->getType(), module);

		thisValue->getField("X") = module.GET("X");
		thisValue->getField("Y") = module.GET("Y");

		}, "X", "Y"));

	Vector2Class.addMethod("__add__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->add(otherValue->callMethod("X", {}, module), module),
			thisValue->getField("Y")->add(otherValue->callMethod("Y", {}, module), module)));
		}, "other"));

	Vector2Class.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->substract(otherValue->callMethod("X", {}, module), module),
			thisValue->getField("Y")->substract(otherValue->callMethod("Y", {}, module), module)));
		}, "other"));

	Vector2Class.addMethod("__multiply__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->multiply(scalar, module),
			thisValue->getField("Y")->multiply(scalar, module)));
		}, "scalar"));

	Vector2Class.addMethod("__divide__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->divide(scalar, module),
			thisValue->getField("Y")->divide(scalar, module)));
		}, "scalar"));

	Vector2Class.addMethod("__equality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->equality(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->equality(otherValue->callMethod("Y", {}, module), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__inequality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->inequality(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->inequality(otherValue->callMethod("Y", {}, module), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__unaryPlus__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->unaryPlus(module),
			thisValue->getField("Y")->unaryPlus(module)));
		}));

	Vector2Class.addMethod("__unaryMinus__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->unaryMinus(module),
			thisValue->getField("Y")->unaryMinus(module)));
		}));

	Vector2Class.addMethod("__less__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->less(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->less(otherValue->callMethod("Y", {}, module), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__greater__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greater(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->greater(otherValue->callMethod("Y", {}, module), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__lessEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->lessEqual(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->lessEqual(otherValue->callMethod("Y", {}, module), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__greaterEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greaterEqual(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->greaterEqual(otherValue->callMethod("Y", {}, module), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__addSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		thisValue->getField("X")->addSet(otherValue->callMethod("X", {}, module), module);
		thisValue->getField("Y")->addSet(otherValue->callMethod("Y", {}, module), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector2Class.addMethod("__substractSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		thisValue->getField("X")->substractSet(otherValue->callMethod("X", {}, module), module);
		thisValue->getField("Y")->substractSet(otherValue->callMethod("Y", {}, module), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector2Class.addMethod("__multiplySet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		thisValue->getField("X")->multiplySet(scalar, module);
		thisValue->getField("Y")->multiplySet(scalar, module);

		RETURN_VALUE(thisValue);
		}, "scalar"));

	Vector2Class.addMethod("__divideSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		thisValue->getField("X")->divideSet(scalar, module);
		thisValue->getField("Y")->divideSet(scalar, module);

		RETURN_VALUE(thisValue);
		}, "scalar"));

	Vector2Class.addMethod("__size__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		Value x = thisValue->getField("X");
		Value y = thisValue->getField("Y");

		RETURN_VALUE(FLOAT(std::sqrt(x->multiply(x, module)->add(y->multiply(y, module), module)->asDouble(module))));
		}));

	Vector2Class.addMethod("__asString__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		RETURN_VALUE(STRING(STRING_LITERAL("X: ") + thisValue->getField("X")->asString(module)
			+ STRING_LITERAL(" Y: ") + thisValue->getField("Y")->asString(module), module));
		}));

	Vector2Class.addMethod("normalize", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value size = thisValue->callMethod("__size__", {}, module);

		if (size->asDouble(module) == 0.0) RETURN_VALUE(thisValue);

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->divide(size, module),
			thisValue->getField("Y")->divide(size, module)));
		}));

	Vector2Class.addMethod("dot", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		RETURN_VALUE(thisValue->getField("X")->multiply(otherValue->callMethod("X", {}, module), module)
			->add(thisValue->getField("Y")->multiply(otherValue->callMethod("Y", {}, module), module), module));
		}, "other"));

	Vector2Class.addMethod("distance", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		Value dx = thisValue->getField("X")->substract(otherValue->callMethod("X", {}, module), module);
		Value dy = thisValue->getField("Y")->substract(otherValue->callMethod("Y", {}, module), module);

		RETURN_VALUE(FLOAT(std::sqrt(dx->asDouble(module)* dx->asDouble(module) +
			dy->asDouble(module) * dy->asDouble(module))));
		}, "other"));

	Vector2Class.addMethod("angleBetween", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);

		Value dot = thisValue->callMethod("dot", { otherValue }, module);
		Value size1 = thisValue->callMethod("__size__", {}, module);
		Value size2 = otherValue->callMethod("__size__", {}, module);

		RETURN_VALUE(FLOAT(std::acos(dot->asDouble(module) /
			(size1->asDouble(module) * size2->asDouble(module)))));
		}, "other"));

	Vector2Class.addMethod("lerp", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");
		Value t = module.GET("t");

		if (!otherValue->instanceOf("Vector2")) throwTypeError(STRING_LITERAL("Vector2"), otherValue->getType(), module);
		if (!isNumber(t)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), t->getType(), module);

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->add(otherValue->callMethod("X", {}, module)->substract(thisValue->getField("X"), module)->multiply(t, module), module),
			thisValue->getField("Y")->add(otherValue->callMethod("Y", {}, module)->substract(thisValue->getField("Y"), module)->multiply(t, module), module)));
		}, "other", "t"));

	Vector.CLASS("Vector2", Vector2Class, module);

	Class Vector3Class;

	Vector3Class.addField("X", FIELD(AccessModifierType::PRIVATE, FLOAT(0)));
	Vector3Class.addField("Y", FIELD(AccessModifierType::PRIVATE, FLOAT(0)));
	Vector3Class.addField("Z", FIELD(AccessModifierType::PRIVATE, FLOAT(0)));

	Vector3Class.addMethod("Vector3", METHOD(AccessModifierType::PUBLIC, [&] {}));

	Vector3Class.addMethod("Vector3", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");

		if (!isNumber(module.GET("X"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("X")->getType(), module);
		if (!isNumber(module.GET("Y"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("Y")->getType(), module);
		if (!isNumber(module.GET("Z"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("Z")->getType(), module);

		thisValue->getField("X") = module.GET("X");
		thisValue->getField("Y") = module.GET("Y");
		thisValue->getField("Z") = module.GET("Z");

		}, "X", "Y", "Z"));

	Vector3Class.addMethod("X", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("X"));
		}));

	Vector3Class.addMethod("X", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!isNumber(module.GET("X"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("X")->getType(), module);
		Value& thisValue = module.GET("this");
		thisValue->getField("X") = FLOAT(module.GET("X")->asDouble(module));
		}, "X"));

	Vector3Class.addMethod("Y", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("Y"));
		}));

	Vector3Class.addMethod("Y", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!isNumber(module.GET("Y"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("Y")->getType(), module);
		Value& thisValue = module.GET("this");
		thisValue->getField("Y") = FLOAT(module.GET("Y")->asDouble(module));
		}, "Y"));

	Vector3Class.addMethod("Z", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.GET("this")->getField("Z"));
		}));

	Vector3Class.addMethod("Z", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!isNumber(module.GET("Z"))) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), module.GET("Z")->getType(), module);
		Value& thisValue = module.GET("this");
		thisValue->getField("Z") = FLOAT(module.GET("Z")->asDouble(module));
		}, "Z"));

	Vector3Class.addMethod("__add__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->add(otherValue->callMethod("X", {}, module), module),
			thisValue->getField("Y")->add(otherValue->callMethod("Y", {}, module), module),
			thisValue->getField("Z")->add(otherValue->callMethod("Z", {}, module), module)));
		}, "other"));

	Vector3Class.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->substract(otherValue->callMethod("X", {}, module), module),
			thisValue->getField("Y")->substract(otherValue->callMethod("Y", {}, module), module),
			thisValue->getField("Z")->substract(otherValue->callMethod("Z", {}, module), module)));
		}, "other"));

	Vector3Class.addMethod("__multiply__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->multiply(scalar, module),
			thisValue->getField("Y")->multiply(scalar, module),
			thisValue->getField("Z")->multiply(scalar, module)));
		}, "scalar"));

	Vector3Class.addMethod("__divide__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->divide(scalar, module),
			thisValue->getField("Y")->divide(scalar, module),
			thisValue->getField("Z")->divide(scalar, module)));
		}, "scalar"));

	Vector3Class.addMethod("__equality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->equality(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->equality(otherValue->callMethod("Y", {}, module), module)->asBool(module) &&
			thisValue->getField("Z")->equality(otherValue->callMethod("Z", {}, module), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__inequality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->inequality(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->inequality(otherValue->callMethod("Y", {}, module), module)->asBool(module) &&
			thisValue->getField("Z")->inequality(otherValue->callMethod("Z", {}, module), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__unaryPlus__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->unaryPlus(module),
			thisValue->getField("Y")->unaryPlus(module),
			thisValue->getField("Z")->unaryPlus(module)));
		}));

	Vector3Class.addMethod("__unaryMinus__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->unaryMinus(module),
			thisValue->getField("Y")->unaryMinus(module),
			thisValue->getField("Z")->unaryMinus(module)));
		}));

	Vector3Class.addMethod("__less__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->less(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->less(otherValue->callMethod("Y", {}, module), module)->asBool(module) &&
			thisValue->getField("Z")->less(otherValue->callMethod("Z", {}, module), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__greater__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greater(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->greater(otherValue->callMethod("Y", {}, module), module)->asBool(module) &&
			thisValue->getField("Z")->greater(otherValue->callMethod("Z", {}, module), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__lessEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->lessEqual(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->lessEqual(otherValue->callMethod("Y", {}, module), module)->asBool(module) &&
			thisValue->getField("Z")->lessEqual(otherValue->callMethod("Z", {}, module), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__greaterEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greaterEqual(otherValue->callMethod("X", {}, module), module)->asBool(module) &&
			thisValue->getField("Y")->greaterEqual(otherValue->callMethod("Y", {}, module), module)->asBool(module) &&
			thisValue->getField("Z")->greaterEqual(otherValue->callMethod("Z", {}, module), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__addSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		thisValue->getField("X")->addSet(otherValue->callMethod("X", {}, module), module);
		thisValue->getField("Y")->addSet(otherValue->callMethod("Y", {}, module), module);
		thisValue->getField("Z")->addSet(otherValue->callMethod("Z", {}, module), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector3Class.addMethod("__substractSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		thisValue->getField("X")->substractSet(otherValue->callMethod("X", {}, module), module);
		thisValue->getField("Y")->substractSet(otherValue->callMethod("Y", {}, module), module);
		thisValue->getField("Z")->substractSet(otherValue->callMethod("Z", {}, module), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector3Class.addMethod("__multiplySet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		thisValue->getField("X")->multiplySet(scalar, module);
		thisValue->getField("Y")->multiplySet(scalar, module);
		thisValue->getField("Z")->multiplySet(scalar, module);

		RETURN_VALUE(thisValue);
		}, "scalar"));

	Vector3Class.addMethod("__divideSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		if (!isNumber(scalar)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), scalar->getType(), module);

		thisValue->getField("X")->divideSet(scalar, module);
		thisValue->getField("Y")->divideSet(scalar, module);
		thisValue->getField("Z")->divideSet(scalar, module);

		RETURN_VALUE(thisValue);
		}, "scalar"));

	Vector3Class.addMethod("__size__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		Value x = thisValue->getField("X");
		Value y = thisValue->getField("Y");
		Value z = thisValue->getField("Z");

		RETURN_VALUE(FLOAT(std::sqrt(x->multiply(x, module)->add(y->multiply(y, module), module)
			->add(z->multiply(z, module), module)->asDouble(module))));
		}));

	Vector3Class.addMethod("__asString__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");

		RETURN_VALUE(STRING(STRING_LITERAL("X: ") + thisValue->getField("X")->asString(module)
			+ STRING_LITERAL(" Y: ") + thisValue->getField("Y")->asString(module)
			+ STRING_LITERAL(" Z: ") + thisValue->getField("Z")->asString(module), module));
		}));

	Vector3Class.addMethod("normalize", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value size = thisValue->callMethod("__size__", {}, module);

		if (size->asDouble(module) == 0.0) RETURN_VALUE(thisValue);

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->divide(size, module),
			thisValue->getField("Y")->divide(size, module),
			thisValue->getField("Z")->divide(size, module)));
		}));

	Vector3Class.addMethod("dot", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		RETURN_VALUE(thisValue->getField("X")->multiply(otherValue->callMethod("X", {}, module), module)
			->add(thisValue->getField("Y")->multiply(otherValue->callMethod("Y", {}, module), module), module)
			->add(thisValue->getField("Z")->multiply(otherValue->callMethod("Z", {}, module), module), module));
		}, "other"));

	Vector3Class.addMethod("distance", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);

		Value dx = thisValue->getField("X")->substract(otherValue->callMethod("X", {}, module), module);
		Value dy = thisValue->getField("Y")->substract(otherValue->callMethod("Y", {}, module), module);
		Value dz = thisValue->getField("Z")->substract(otherValue->callMethod("Z", {}, module), module);

		RETURN_VALUE(FLOAT(std::sqrt(dx->asDouble(module) * dx->asDouble(module) +
			dy->asDouble(module) * dy->asDouble(module) +
			dz->asDouble(module) * dz->asDouble(module))));
		}, "other"));

	Vector3Class.addMethod("lerp", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");
		Value t = module.GET("t");

		if (!otherValue->instanceOf("Vector3")) throwTypeError(STRING_LITERAL("Vector3"), otherValue->getType(), module);
		if (!isNumber(t)) throwTypeError(STRING_LITERAL("int"), STRING_LITERAL("float"), t->getType(), module);

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->add(otherValue->callMethod("X", {}, module)->substract(thisValue->getField("X"), module)->multiply(t, module), module),
			thisValue->getField("Y")->add(otherValue->callMethod("Y", {}, module)->substract(thisValue->getField("Y"), module)->multiply(t, module), module),
			thisValue->getField("Z")->add(otherValue->callMethod("Z", {}, module)->substract(thisValue->getField("Z"), module)->multiply(t, module), module)));
		}, "other", "t"));

	Vector.CLASS("Vector3", Vector3Class, module);

	modules.emplace(STRING_LITERAL("Vector"), Vector);
}