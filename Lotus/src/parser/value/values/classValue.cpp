#include "parser/value/classValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"

using namespace lotus;

Value lotus::ClassValue::sizeInRam() {
    return INT(sizeof(ClassValue));
}