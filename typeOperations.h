/**
 * @file contém a declaração das funções correspondentes às operações de conversão de tipo
 * sobre a stack
 */

//! Include guard
#ifndef TYPE_OPERATIONS_H
//! Include guard
#define TYPE_OPERATIONS_H

#define UNDEFINED 13

#include "stack.h"


Value convertToInt(Value v);
Value convertToDouble(Value v);
Value convertToChar(Value v);
Value convertToString(Value v);

char* convertFloatToString(double v);
char* convertIntToString(long long v);
char* convertCharToString(char v);

Value convertToType(DataType, Value);

Value convertAndDisposeToDouble(Value);
Value convertAndDisposeToInt(Value);
Value convertAndDisposeToChar(Value);
Value convertAndDisposeToString(Value);

#endif
