/**
 * 
 * @file contém as definições das funções usadas para processar o input e 
 * preencher a stack fornecida.
 * 
 */

#ifndef PARSER_H
/*! Include guard */
#define PARSER_H


#include "stack.h"
#include "operations.h"
#include "stackOperations.h"
#include "typeOperations.h"
#include "logicOperations.h"


#define POP_0S st
#define POP_1 pop(st)
#define POP_1S st, pop(st)
#define POP_1O str + 1, pop(st)
#define POP_2 pop(st), pop(st)
#define POP_2O str + 1, pop(st), pop(st)

#define PUSH_0S(x,y) y
#define PUSH_1(x,y) push(x,y)
#define PUSH_1S(x,y) push(x,y)
#define PUSH_1O(x,y) push(x,y)
#define PUSH_2(x,y) push(x,y)
#define PUSH_2O(x,y) push(x,y)

#define JUMP_TABLE \
        ENTRY('l', readLine, 0S) \
        ENTRY(';', erase, 0S) \
        ENTRY('_', duplicate, 0S) \
        ENTRY('\\', swap, 0S) \
        ENTRY('@', rotate, 0S) \
        \
        \
        ENTRY('(', decrement, 1) \
        ENTRY(')', increment, 1) \
        ENTRY('~', negate, 1) \
        ENTRY('f', convertAndDisposeToDouble, 1) \
        ENTRY('i', convertAndDisposeToInt, 1) \
        ENTRY('c', convertAndDisposeToChar, 1) \
        ENTRY('s', convertAndDisposeToString, 1) \
        \
        ENTRY('$', getElement, 1S) \
        \
        ENTRY(':', setVariable, 1O) \
        \
        \
        ENTRY('+', sum, 2) \
        ENTRY('-', subtract, 2) \
        ENTRY('*', multiply, 2) \
        ENTRY('/', divide, 2) \
        ENTRY('%', module, 2) \
        ENTRY('#', exponentiate, 2) \
        ENTRY('&', and, 2) \
        ENTRY('|', or, 2) \
        ENTRY('^', xor, 2) \
        \
        ENTRY('e', shortcutSelect, 2O) \



bool operation(char*, Stack);

Value readValue(char* str);

void resolveWord(char*, int, Stack);

void processInput(char* str, Stack st);

void printVal(Value);

void printStack(Stack st);

void printStackLine(Stack st);

#endif
