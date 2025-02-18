#include "parser/statement/importStatement.h"
#include "utils/utils.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::ImportStatement::ImportStatement(const String& key, const String& filePath, Module& currentModule, StringMap<Module>& modules, const Flags& flags)
    : key(key), filePath(filePath), currentModule(currentModule), modules(modules), flags(flags) {}

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

        parser = MAKE_PTR<Parser>(tokens);

        auto statements = parser->parse();

        for (auto& statement : statements) {
            if (statement) {
                statement->execute();
            }
        }

        module = parser->getModule();
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
                currentModule.variables.forceDeclareOrSet(variable.first, variable.second);
            }
            else currentModule.variables.declare(variable.first, variable.second);
        }

        for (auto& function : module.functions.functions) {

            if (allowOverwrite) {
                currentModule.functions.forceDeclareOrSet(function.first, function.second);
            }
            else currentModule.functions.declare(function.first, function.second);
        }

        for (auto& Static : module.statics.statics) {

            if (allowOverwrite) {
                currentModule.statics.forceDeclareOrSet(Static.first, Static.second);
            }
            else currentModule.statics.declare(Static.first, Static.second);
        }
    }
    else if (module.statics.isExists(key)) {

        if (allowOverwrite) {
            currentModule.statics.forceDeclareOrSet(key, module.statics.get(key));
        }
        else currentModule.statics.declare(key, module.statics.get(key));
    }
    else if (module.variables.isExists(key)) {

        if (allowOverwrite) {
            currentModule.variables.forceDeclareOrSet(key, module.variables.get(key));
        }
        else currentModule.variables.declare(key, module.variables.get(key));
    }
    else if (module.functions.isExists(key)) {
        currentModule.functions.declare(key, module.functions.get(key));
    }
    else {
        throw LotusException(STRING_LITERAL("\"") + key + STRING_LITERAL("\"") + 
            String(STRING_LITERAL(" not found in ")) + STRING_LITERAL("\"") + filePath + STRING_LITERAL("\""));
    }
}
