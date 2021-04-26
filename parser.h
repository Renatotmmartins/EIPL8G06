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

//! Seleciona os argumentos das funções sobre a stack
#define POP_0S st->stack
//! Seleciona o argumento das funções com um arguemnto
#define POP_1 pop(st->stack)
//! Seleciona o argumento das funções com um argumento sobre a stack
#define POP_1S st->stack, pop(st->stack)
//! Seleciona o argumento das funções com um argumento e sub operações
#define POP_1SO *(str + 1), st, pop(st->stack)
//! Seleciona o argumento das funções com dois argumentos
#define POP_2 pop(st->stack), pop(st->stack)
//! Seleciona o argumento das funções com dois argumentos e sub operações
#define POP_2O str + 1, pop(st->stack), pop(st->stack)
//! Seleciona o argumento das funções com três argumentos
#define POP_3 pop(st->stack), pop(st->stack), pop(st->stack)

//! Não efetua push do resultado da operação.
#define PUSH_0S(x,y) y
//! Efetua push do resultado da operação.
#define PUSH_1(x,y) push(x,y)
//! Efetua push do resultado da operação.
#define PUSH_1S(x,y) push(x,y)
//! Efetua push do resultado da operação.
#define PUSH_1SO(x,y) push(x,y)
//! Efetua push do resultado da operação.
#define PUSH_2(x,y) push(x,y)
//! Efetua push do resultado da operação.
#define PUSH_2O(x,y) push(x,y)
//! Efetua push do resultado da operação.
#define PUSH_3(x,y) push(x,y)

//! Contém o registo de todos os operadores e respetivos argumentos
#define JUMP_TABLE \
        ENTRY('l', readLine, 0S) \
        ENTRY('_', duplicate, 0S) \
        ENTRY(';', eraseTop, 0S) \
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
        ENTRY('!', logicNot,1) \
        \
        ENTRY('$', copyElement, 1S) \
        \
        ENTRY(':', setVariable, 1SO) \
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
        ENTRY('=', isEqual, 2) \
        ENTRY('<', isLess, 2) \
        ENTRY('>', isGreater, 2) \
        \
        ENTRY('e', shortcutSelect, 2O) \
        \
        \
        ENTRY('?', conditional, 3)



bool operation(char* str, State* st);

Value readValue(char* str, State* st);

char getControlChar(char);

Value readString(char**);

void resolveWord(char* str, int length, State* st);

void processInput(char** str, State* st);

void printVal(Value val);

void printStack(Stack st);

void printStackLine(Stack st);

#endif
