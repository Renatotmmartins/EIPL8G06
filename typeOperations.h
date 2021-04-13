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

Value convertFloatToString(Value v);
Value convertIntToString(Value v);
Value convertCharToString(Value v);
Value copyString(Value v);

#endif