#ifndef PARSER_H
#define PARSER_H

/**
 * 
 * @file contém as definições das funções usadas para processar o input e 
 * preencher a stack fornecida.
 * 
 */

#include "stack.h"

/**
 * Verifica se o caracter fornecido é um algarismo.
 * 
 * @param ch O caracter fornecido
 * @return   Se for um algarismo, 1, senão, 0
 */
bool isNumeric(char ch);

/**
 * Calcula o número de operandos exigidos pela operação definida pelo
 * caracter dado.
 * 
 * @param ch O caracter fornecido
 * @return   O número de operandos exigidos pela respetiva operação (-1 caso
 *           o caracter não codifique nenhuma operação)
 */
int numberOperands (char ch);

/**
 * Executa a operação definida pelo caracter dado, a qual exige dois operandos,
 * x e y, na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param x  O primeiro operando
 * @param y  O segundo operando
 * @param ch O caracter que define a operação a executar
 */
void twoOperand(struct stack* st, int x, int y, char ch);

/**
 * Executa a operação definida pelo caracter dado, a qual exige um operando x,
 * na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param x  O operando
 * @param ch O caracter que define a operação a executar
 */
void oneOperand(struct stack* st, int x, char ch);

#endif
