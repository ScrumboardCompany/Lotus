#include "parser/parser.h"
#include "parser/statement/flagStatement.h"
#include "utils/lotusError.h"

using namespace lotus;

Statement Parser::handleFlagStatement() {
	String flag = consume(TokenType::WORD).text;

	bool value;

	if (match(TokenType::TRUE)) {
		value = true;
	}
	else if (match(TokenType::FALSE)) {
		value = false;
	}
	else {
		throw LotusException(STRING_LITERAL("Required true or false"));
	}

	return MAKE_PTR<FlagStatement>(flag, value, flags);
}