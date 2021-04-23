#include "stack.h"
#include "parser.h"

bool isTrue(Value a);

Value shortcutSelect(char*, Value, Value);

Value setVariable(char* var, Value x);