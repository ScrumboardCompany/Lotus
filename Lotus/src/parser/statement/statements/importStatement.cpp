#include "parser/statement/importStatement.h"
#include "utils/utils.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "structures/variables.h"
#include "utils/lotusError.h"
#include "structures/classes.h"

using namespace lotus;

lotus::ImportStatement::ImportStatement(const String& key, const String& filePath, Module& currentModule, StringMap<Module>& modules, const Flags& flags)
    : key(key), filePath(filePath), currentModule(currentModule), modules(modules), flags(flags) {}

void lotus::ImportStatement::execute() {
    size_t find = filePath.find_last_of(CHAR_LITERAL('/'));
    String file = (find != String::npos) ? filePath.substr(find + 1) : filePath;

    Module module;

    if (file.find(CHAR_LITERAL('.')) != String::npos) {
        String content = lotus::wreadContent(filePath);
        Lexer lexer(content);
        auto tokens = lexer.tokenize();
        parser = MAKE_PTR<Parser>(tokens);
        auto statements = parser->parse();
        for (auto& statement : statements) {
            if (statement) statement->execute();
        }
        module = parser->getModule();
    }
    else {
        if (modules.find(file) == modules.end()) {
            throw LotusException(STRING_LITERAL("Module: ") + file + STRING_LITERAL(" not found"));
        }
        module = modules[file];
    }

    bool importEverythingWithSameName = flags.getImportEverythingWithSameName();
    bool importAll = (key == STRING_LITERAL("*"));

    if (importAll) {
        for (auto& cls : module.classes.classes) {
            if (!currentModule.classes.isExists(cls.first)) {
                currentModule.classes.declare(cls.first, cls.second);
                currentModule.classes.registerClass(cls.first, currentModule.functions, currentModule.variables);
            }
        }
        for (auto& stat : module.statics.statics) {
            if (!currentModule.statics.isExists(stat.first))
                currentModule.statics.forceSet(stat.first, stat.second);
        }
        for (auto& func : module.functions.functions) {
            if (!currentModule.functions.isExists(func.first) && !module.classes.isExists(func.first)) {
                for (auto& f : func.second) {
                    currentModule.functions.forceSet(func.first, f);
                }
            }
        }
        if (!module.variables.scopes.empty())
        for (auto& var : module.variables.scopes[0]) {
            if (!currentModule.variables.isExists(var.first))
                currentModule.variables.forceSet(var.first, var.second);
        }
    }
    else {
        bool found = false;
        if (module.classes.isExists(key)) {
            currentModule.classes.declare(key, module.classes.get(key));
            currentModule.classes.registerClass(key, currentModule.functions, currentModule.variables);
            found = true;
        }
        if (module.statics.isExists(key)) {
            if (importEverythingWithSameName || !found) {
                currentModule.statics.forceSet(key, module.statics.get(key));
                found = true;
            }
        }
        if (module.functions.isExists(key)) {
            if ((importEverythingWithSameName || !found) && !module.classes.isExists(key)) {
                for (auto& f : module.functions.functions[key]) {
                    currentModule.functions.declare(key, f);
                }
                found = true;
            }
        }
        if (module.variables.isExists(key)) {
            if (importEverythingWithSameName || !found) {
                currentModule.variables.forceSet(key, module.variables.get(key));
                found = true;
            }
        }

        if (!found) throw LotusException(STRING_LITERAL("\"") + key + STRING_LITERAL("\"") +
            String(STRING_LITERAL(" not found in ")) + STRING_LITERAL("\"") + filePath + STRING_LITERAL("\""));
    }
}
