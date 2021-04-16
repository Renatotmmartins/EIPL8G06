/**
 * @file contém a declaração das funções correspondentes às operações de conversão de tipo
 * sobre a stack
 */

//! Include guard
#ifndef TYPE_OPERATIONS_H
//! Include guard
#define TYPE_OPERATIONS_H

#include "stack.h"

Value convertToInt(Value v);
Value convertToDouble(Value v);
Value convertToChar(Value v);
Value convertToString(Value v);

char* convertFloatToString(Value v);
char* convertIntToString(Value v);
char* convertCharToString(Value v);
char* copyString(Value v);

#endif
