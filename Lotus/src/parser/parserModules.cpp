#include "parser/parser.h"

void lotus::Parser::loadModules() {
	loadStandardModule();
	loadMathModule();
	loadTimeModule();
	loadOsModule();
	loadVectorModule();
}