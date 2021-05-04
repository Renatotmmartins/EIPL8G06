/**
 * @file contém a declaração das funções correspondentes
 * às operações relacionadas com os blocos
 */

//! Include guard
#ifndef BLOCK_OPERATIONS_H
//! Include guard
#define BLOCK_OPERATIONS_H

#include "stack.h"
#include "logicOperations.h"

Value execute (Stack st, Value block);

Void execute_while_true (Stack st, Value block);


#endif