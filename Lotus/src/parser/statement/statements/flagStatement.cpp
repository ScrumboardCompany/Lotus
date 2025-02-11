#include "parser/statement/flagStatement.h"
#include "structures/flags.h"

using namespace lotus;

lotus::FlagStatement::FlagStatement(const String& flag, bool value, Flags& flags)
	: flag(flag), value(value), flags(flags) {}

void lotus::FlagStatement::execute() {
	flags.set(flag, value);
}