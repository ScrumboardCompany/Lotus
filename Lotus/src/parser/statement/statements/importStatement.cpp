#include "parser/statement/importStatement.h"
#include "utils/utils.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::ImportStatement::ImportStatement(const String& key, const String& filePath, Variables& variables, Functions& functions, StringMap<Module>& modules, const Flags& flags)
    : key(key), filePath(filePath), variables(variables), functions(functions), modules(modules), flags(flags) {}

void lotus::ImportStatement::execute() {

    size_t find = filePath.find_last_of(CHAR_LITERAL('/'));
    String file;

    if (find != String::npos) {
        file = filePath.substr(find + 1, file.size() - find);
    }
    else {
        file = filePath;
    }

    Module module;

    if (file.find(CHAR_LITERAL('.')) != String::npos) {

        lotus::String content = lotus::wreadContent(filePath);

        Lexer lexer(content);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);

        auto statements = parser.parse();

        for (auto& statement : statements) {
            if (statement) {
                statement->execute();
            }
        }

        module = parser.getModule();
    }
    else {
        if (modules.find(file) == modules.end()) {
            throw LotusException(STRING_LITERAL("Module: ") + file + STRING_LITERAL(" not found"));
        }

        module = modules[file];
    }

    bool allowOverwrite = flags.getAllowOverwrite();

    if (key == STRING_LITERAL("*") /* check needed to import all */) {
        for (auto& variable : module.variables.variables) {

            if (allowOverwrite) {
                variables.forceDeclareOrSet(variable.first, variable.second);
            }
            else variables.declare(variable.first, variable.second);
        }

        for (auto& function : module.functions.functions) {

            if (allowOverwrite) {
                functions.forceDeclareOrSet(function.first, function.second);
            }
            else functions.declare(function.first, function.second);
        }
    }
    else if (module.variables.isExists(key)) {

        if (allowOverwrite) {
            variables.forceDeclareOrSet(key, module.variables.get(key));
        }
        else variables.declare(key, module.variables.get(key));
    }
    else if (module.functions.isExists(key)) {
        functions.declare(key, module.functions.get(key));
    }
    else {
        throw LotusException(STRING_LITERAL("\"") + key + STRING_LITERAL("\"") + 
            String(STRING_LITERAL(" not found in ")) + STRING_LITERAL("\"") + filePath + STRING_LITERAL("\""));
    }
}
