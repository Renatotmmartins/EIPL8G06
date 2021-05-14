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

bool isEmptyBlock(char* a);

void execute (State* s, Stack st, Value block);

Value executeValue(State* s, Value a, Value block);

void executeWhileTrue (State* s, Value block);

void map (State* s, Stack st, Value block);

void filter (State* s, Stack st, Value block);

void fold (State* s, Stack st, Value block);

#endif