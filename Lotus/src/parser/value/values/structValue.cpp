#include "parser/value/structValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"

using namespace lotus;

Value lotus::StructValue::sizeInRam() {
    return INT(sizeof(StructValue));
}