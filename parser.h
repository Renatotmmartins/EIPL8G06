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

bool isNumeric(char ch);

int numberOperands (char ch);

void twoOperands(Stack* st, Value x, Value y, char ch);

void oneOperand(Stack* st, Value x, char ch);

void zeroOperands(Stack* st, char ch);

void operation (Stack* st, char ch);

void processInput(char* str, Stack* st);

void printStack(Stack* st);

void printStackLine(Stack* st);

#endif
