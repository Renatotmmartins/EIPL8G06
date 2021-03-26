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

void twoOperand(struct stack* st, int x, int y, char ch);

void oneOperand(struct stack* st, int x, char ch);

void operation (struct stack* st, char ch);

void processInput(char* str, struct stack* st);

void printStack(struct stack* st);

void printStackLine(struct stack* st);

#endif
