#include "parser/parser.h"
#include "utils/lotusError.h"

using namespace lotus;

Statement Parser::handleFlagStatement() {
	String flag = consume(TokenType::IDENTIFIER).text;

	bool value;

	if (match(TokenType::DEFAULT)) {
		module.flags.setDefault(flag);
		return nullptr;
	}
	else if (match(TokenType::TRUE)) {
		value = true;
	}
	else if (match(TokenType::FALSE)) {
		value = false;
	}
	else {
		throw LotusException(STRING_LITERAL("Required flag value"), get(0).line);
	}

	module.flags.set(flag, value);
	return nullptr;
}