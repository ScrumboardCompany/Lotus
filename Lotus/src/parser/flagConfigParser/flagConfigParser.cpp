#include "parser/flagConfigParser/flagConfigParser.h"
#include "utils/lotusError.h"

using namespace lotus;

Token lotus::FlagConfigParser::get(const size_t relativePosition) {
	const size_t position = pos + relativePosition;
	if (position >= tokens.size()) return EOF_TOKEN;
	return tokens.at(position);
}

bool lotus::FlagConfigParser::match(const TokenType type) {
	const Token CurrentToken = get(0);
	if (type != CurrentToken.type) return false;
	pos++;

	return true;
}

Token lotus::FlagConfigParser::consume(const TokenType type) {
	const Token CurrentToken = get(0);
	if (type != CurrentToken.type) {
		throw LotusException(STRING_LITERAL("Expected ") + Token({ type, STRING_LITERAL("") }).type_to_string() + STRING_LITERAL(" instead of ") + CurrentToken.type_to_string());
	}
	pos++;

	return CurrentToken;
}

lotus::FlagConfigParser::FlagConfigParser(const std::list<Token>& tokens) : pos(0) {
	this->tokens.clear();
	for (auto& token : tokens) {
		this->tokens.push_back(token);
	}
}

void lotus::FlagConfigParser::parse() {
	while (!match(TokenType::END_OF_FILE)) {
		if (get(0).type == TokenType::IDENTIFIER) {
			String flagName = consume(TokenType::IDENTIFIER).text;

			consume(TokenType::EQUAL);

			bool value;

			if (match(TokenType::TRUE)) {
				value = true;
			}
			else if (match(TokenType::FALSE)) {
				value = false;
			}
			else {
				throw LotusException(STRING_LITERAL("Expected true or false in flag config"));
			}

			flags[flagName] = value;
		}
		match(TokenType::COMMA);
	}
}

StringMap<bool> lotus::FlagConfigParser::getFlags() const {
	return flags;
}
