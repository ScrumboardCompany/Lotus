#include "parser/parser.h"

using namespace lotus;

Expression lotus::Parser::expression() {
	return additive();
}