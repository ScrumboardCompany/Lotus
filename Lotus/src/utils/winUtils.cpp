#include "utils/utils.h"
#include <io.h>
#include <fcntl.h>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

void lotus::setConsoleLocale() {
    std::locale::global(std::locale(""));

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}