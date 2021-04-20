#include "stack.h"
#include "parser.h"

#define SELECT_0S(x,y) st
#define SELECT_1(x,y) x
#define SELECT_1S(x,y) st, x
#define SELECT_1O(x,y) str + 1, x
#define SELECT_2(x,y) x, y
#define SELECT_2O(x,y) str + 1, x, y

#define RETURN_0S(x) v
#define RETURN_1(x) x
#define RETURN_1S(x) v
#define RETURN_1O(x) x
#define RETURN_2(x) x
#define RETURN_2O(x) x

bool isTrue(Value a);

Value shortcutSelect(char*, Value, Value);

Value setVariable(char* var, Value x);