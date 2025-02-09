#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"

using namespace lotus;

lotus::Parser::Parser(const std::list<Token>& tokens) : pos(0) {
	this->tokens.clear();
	for (auto& token : tokens) {
		this->tokens.push_back(token);
	}
}

Expression lotus::Parser::parse() {
	return expression();
}
