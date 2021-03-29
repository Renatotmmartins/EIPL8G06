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

void twoOperand(Stack* st, int x, int y, char ch);

void oneOperand(Stack* st, int x, char ch);

void operation (Stack* st, char ch);

void processInput(char* str, Stack* st);

void printStack(Stack* st);

void printStackLine(Stack* st);

#endif
