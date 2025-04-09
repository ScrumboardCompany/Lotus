#include "parser/parser.h"

using namespace lotus;

StringMap<Module> Parser::modules;

void lotus::Parser::loadModules() {
	loadMathModule();
	loadTimeModule();
	loadOsModule();
	loadVectorModule();
	loadUtilityModule();
}