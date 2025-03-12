#include "parser/parser.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/stringValue.h"

using namespace lotus;

void lotus::Parser::loadVectorModule() {
	Module Vector;

	Class Vector2Class;

	Vector2Class.addField("X", FIELD(AccessModifierType::PUBLIC, FLOAT(0)));
	Vector2Class.addField("Y", FIELD(AccessModifierType::PUBLIC, FLOAT(0)));

	Vector2Class.addMethod("Vector2", METHOD(AccessModifierType::PUBLIC, [&] {}));

	Vector2Class.addMethod("Vector2", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");

		thisValue->getField("X") = module.GET("X");
		thisValue->getField("Y") = module.GET("Y");

		}, "X", "Y"));

	Vector2Class.addMethod("__add__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->add(otherValue->getField("X"), module),
			thisValue->getField("Y")->add(otherValue->getField("Y"), module)));
		}, "other"));

	Vector2Class.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->substract(otherValue->getField("X"), module),
			thisValue->getField("Y")->substract(otherValue->getField("Y"), module)));
		}, "other"));

	Vector2Class.addMethod("__multiply__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->multiply(scalar, module),
			thisValue->getField("Y")->multiply(scalar, module)));
		}, "scalar"));

	Vector2Class.addMethod("__divide__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->divide(scalar, module),
			thisValue->getField("Y")->divide(scalar, module)));
		}, "scalar"));

	Vector2Class.addMethod("__equality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->equality(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->equality(otherValue->getField("Y"), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__inequality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->inequality(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->inequality(otherValue->getField("Y"), module)->asBool(module)));
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

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->less(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->less(otherValue->getField("Y"), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__greater__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greater(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->greater(otherValue->getField("Y"), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__lessEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->lessEqual(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->lessEqual(otherValue->getField("Y"), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__greaterEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greaterEqual(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->greaterEqual(otherValue->getField("Y"), module)->asBool(module)));
		}, "other"));

	Vector2Class.addMethod("__addSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		thisValue->getField("X")->addSet(thisValue->getField("X"), module);
		thisValue->getField("Y")->addSet(thisValue->getField("Y"), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector2Class.addMethod("__substractSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		thisValue->getField("X")->substractSet(thisValue->getField("X"), module);
		thisValue->getField("Y")->substractSet(thisValue->getField("Y"), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector2Class.addMethod("__multiplySet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		thisValue->getField("X")->multiplySet(scalar, module);
		thisValue->getField("Y")->multiplySet(scalar, module);

		RETURN_VALUE(thisValue);
		}, "scalar"));

	Vector2Class.addMethod("__divideSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

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
			+ STRING_LITERAL(" Y: ") + thisValue->getField("Y")->asString(module)));
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

		RETURN_VALUE(thisValue->getField("X")->multiply(otherValue->getField("X"), module)
			->add(thisValue->getField("Y")->multiply(otherValue->getField("Y"), module), module));
		}, "other"));

	Vector2Class.addMethod("distance", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		Value dx = thisValue->getField("X")->substract(otherValue->getField("X"), module);
		Value dy = thisValue->getField("Y")->substract(otherValue->getField("Y"), module);

		RETURN_VALUE(FLOAT(std::sqrt(dx->asDouble(module)* dx->asDouble(module) +
			dy->asDouble(module) * dy->asDouble(module))));
		}, "other"));

	Vector2Class.addMethod("angleBetween", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

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

		RETURN_VALUE(module.CALL("Vector2",
			thisValue->getField("X")->add(otherValue->getField("X")->substract(thisValue->getField("X"), module)->multiply(t, module), module),
			thisValue->getField("Y")->add(otherValue->getField("Y")->substract(thisValue->getField("Y"), module)->multiply(t, module), module)));
		}, "other", "t"));

	Vector.CLASS("Vector2", Vector2Class, module, true);

	Class Vector3Class;

	Vector3Class.addField("X", FIELD(AccessModifierType::PUBLIC, FLOAT(0)));
	Vector3Class.addField("Y", FIELD(AccessModifierType::PUBLIC, FLOAT(0)));
	Vector3Class.addField("Z", FIELD(AccessModifierType::PUBLIC, FLOAT(0)));

	Vector3Class.addMethod("Vector3", METHOD(AccessModifierType::PUBLIC, [&] {}));

	Vector3Class.addMethod("Vector3", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");

		thisValue->getField("X") = module.GET("X");
		thisValue->getField("Y") = module.GET("Y");
		thisValue->getField("Z") = module.GET("Z");

		}, "X", "Y", "Z"));

	Vector3Class.addMethod("__add__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->add(otherValue->getField("X"), module),
			thisValue->getField("Y")->add(otherValue->getField("Y"), module),
			thisValue->getField("Z")->add(otherValue->getField("Z"), module)));
		}, "other"));

	Vector3Class.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->substract(otherValue->getField("X"), module),
			thisValue->getField("Y")->substract(otherValue->getField("Y"), module),
			thisValue->getField("Z")->substract(otherValue->getField("Z"), module)));
		}, "other"));

	Vector3Class.addMethod("__multiply__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->multiply(scalar, module),
			thisValue->getField("Y")->multiply(scalar, module),
			thisValue->getField("Z")->multiply(scalar, module)));
		}, "scalar"));

	Vector3Class.addMethod("__divide__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->divide(scalar, module),
			thisValue->getField("Y")->divide(scalar, module),
			thisValue->getField("Z")->divide(scalar, module)));
		}, "scalar"));

	Vector3Class.addMethod("__equality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->equality(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->equality(otherValue->getField("Y"), module)->asBool(module) &&
			thisValue->getField("Z")->equality(otherValue->getField("Z"), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__inequality__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->inequality(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->inequality(otherValue->getField("Y"), module)->asBool(module) &&
			thisValue->getField("Z")->inequality(otherValue->getField("Z"), module)->asBool(module)));
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

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->less(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->less(otherValue->getField("Y"), module)->asBool(module) &&
			thisValue->getField("Z")->less(otherValue->getField("Z"), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__greater__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greater(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->greater(otherValue->getField("Y"), module)->asBool(module) &&
			thisValue->getField("Z")->greater(otherValue->getField("Z"), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__lessEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->lessEqual(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->lessEqual(otherValue->getField("Y"), module)->asBool(module) &&
			thisValue->getField("Z")->lessEqual(otherValue->getField("Z"), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__greaterEqual__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		RETURN_VALUE(BOOL(
			thisValue->getField("X")->greaterEqual(otherValue->getField("X"), module)->asBool(module) &&
			thisValue->getField("Y")->greaterEqual(otherValue->getField("Y"), module)->asBool(module) &&
			thisValue->getField("Z")->greaterEqual(otherValue->getField("Z"), module)->asBool(module)));
		}, "other"));

	Vector3Class.addMethod("__addSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		thisValue->getField("X")->addSet(otherValue->getField("X"), module);
		thisValue->getField("Y")->addSet(otherValue->getField("Y"), module);
		thisValue->getField("Z")->addSet(otherValue->getField("Z"), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector3Class.addMethod("__substractSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		thisValue->getField("X")->substractSet(otherValue->getField("X"), module);
		thisValue->getField("Y")->substractSet(otherValue->getField("Y"), module);
		thisValue->getField("Z")->substractSet(otherValue->getField("Z"), module);

		RETURN_VALUE(thisValue);
		}, "other"));

	Vector3Class.addMethod("__multiplySet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

		thisValue->getField("X")->multiplySet(scalar, module);
		thisValue->getField("Y")->multiplySet(scalar, module);
		thisValue->getField("Z")->multiplySet(scalar, module);

		RETURN_VALUE(thisValue);
		}, "scalar"));

	Vector3Class.addMethod("__divideSet__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& thisValue = module.GET("this");
		Value scalar = module.GET("scalar");

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
			+ STRING_LITERAL(" Z: ") + thisValue->getField("Z")->asString(module)));
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

		RETURN_VALUE(thisValue->getField("X")->multiply(otherValue->getField("X"), module)
			->add(thisValue->getField("Y")->multiply(otherValue->getField("Y"), module), module)
			->add(thisValue->getField("Z")->multiply(otherValue->getField("Z"), module), module));
		}, "other"));

	Vector3Class.addMethod("distance", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");

		Value dx = thisValue->getField("X")->substract(otherValue->getField("X"), module);
		Value dy = thisValue->getField("Y")->substract(otherValue->getField("Y"), module);
		Value dz = thisValue->getField("Z")->substract(otherValue->getField("Z"), module);

		RETURN_VALUE(FLOAT(std::sqrt(dx->asDouble(module) * dx->asDouble(module) +
			dy->asDouble(module) * dy->asDouble(module) +
			dz->asDouble(module) * dz->asDouble(module))));
		}, "other"));

	Vector3Class.addMethod("lerp", METHOD(AccessModifierType::PUBLIC, [&] {
		Value thisValue = module.GET("this");
		Value otherValue = module.GET("other");
		Value t = module.GET("t");

		RETURN_VALUE(module.CALL("Vector3",
			thisValue->getField("X")->add(otherValue->getField("X")->substract(thisValue->getField("X"), module)->multiply(t, module), module),
			thisValue->getField("Y")->add(otherValue->getField("Y")->substract(thisValue->getField("Y"), module)->multiply(t, module), module),
			thisValue->getField("Z")->add(otherValue->getField("Z")->substract(thisValue->getField("Z"), module)->multiply(t, module), module)));
		}, "other", "t"));

	Vector.CLASS("Vector3", Vector3Class, module, true);

	modules.emplace(STRING_LITERAL("Vector"), Vector);
}