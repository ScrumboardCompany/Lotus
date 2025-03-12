#include "structures/enum.h"
#include "utils/lotusError.h"
#include "parser/value/value.h"
#include "parser/value/intValue.h"

using namespace lotus;

void lotus::Enum::addElement(const String& key, Value value, Module& module) {
	if (value->instanceOf("int") || value->instanceOf("string") || value->instanceOf("undefined")) {

		if (value->instanceOf("undefined")) {
			if (elements.empty()) {
				value = INT(0);
			}
			else if (elements.begin()->second->instanceOf("int")) {
				Int maxValue = elements.begin()->second->asInt(module);
				for (auto& element : elements) {
					Int elementValue = element.second->asInt(module);
					if (elementValue > maxValue) {
						maxValue = elementValue;
					}
				}
				value = INT(maxValue + 1);
			}
			else {
				throw LotusException(STRING_LITERAL("When enum elements are of type string, all elements must be initialized"));
			}
		}

		for (auto& element : elements) {
			if (value->getType() != element.second->getType()) {
				throw LotusException(STRING_LITERAL("Enum can only store one type"));
			}
			if (element.second->equality(value, module)->asBool(module)) {
				throw LotusException(STRING_LITERAL("Enum cannot have two same values"));
			}
		}

		elements.emplace(key, value);
	}
	else {
		throw LotusException(STRING_LITERAL("Element of enum type can only be int or string"));
	}
}

void lotus::Enum::addElement(const char* key, const Value& value, Module& module) {
	addElement(STRING_VAR_LITERAL(key), value, module);
}

Value& lotus::Enum::getElement(const String& key) {
	if (isExists(key)) {
		return elements[key];
	}

	throw LotusException(STRING_LITERAL("Undefined element \"") + key + STRING_LITERAL("\""));
}

Value& lotus::Enum::getElement(const char* key) {
	return getElement(STRING_VAR_LITERAL(key));
}

bool lotus::Enum::isExists(const String& key) {
	return elements.find(key) != elements.end();
}

bool lotus::Enum::isExists(const char* key) {
	return isExists(STRING_VAR_LITERAL(key));
}
