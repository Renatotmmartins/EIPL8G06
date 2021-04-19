/**
 * 
 * @file contém a implementação das funções usadas para processar o input e 
 * preencher a stack fornecida
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.h"
#include "operations.h"
#include "typeOperations.h"


#define POP_0 st
#define POP_1 pop(st)
#define POP_2 pop(st), pop(st)

#define PUSH_0(x,y) y
#define PUSH_1(x,y) push(x,y)
#define PUSH_2(x,y) push(x,y)

#define JUMP_TABLE \
        ENTRY('+',sum,2) \
        ENTRY('~',negate,1)

/**
 * \brief Verifica se o caracter fornecido é um algarismo.
 * 
 * @param ch O caracter fornecido
 * @return   Se for um algarismo, 1, senão, 0
 */
bool isNumeric(char ch) {
    return (ch - '0' >= 0 && ch - '0' <= 9);
}

int operation2(char ch, Stack* st) {
    #define ENTRY(a,b,c) if(ch == a) {PUSH_##c(st, b(POP_##c )); return c;}
            JUMP_TABLE
    #undef ENTRY

    return -1;
}


Value castToValue(char* str)  {
    return fromInteger(atoi(str));
}

/**
 * \brief Processa a palavra fornecida, preenchendo a stack dada ou efetuando a operação descrita.
 * 
 * @param str       A string correspondente à palavra
 * @param length    O tamanho da palavra
 * @param st        A stack a preencher
 */
void resolveWord(char* str, int length, Stack* st)
{
    if (length <= 0)
        return;

    if(operation2(*str, st) == -1)
        push(st, castToValue(str));
}


/**
 * \brief Processa a string fornecida, e preenche a stack dada, efetuando todas as operações descritas na string.
 * 
 * @param str   A string correspondente ao input
 * @param st    A stack a preencher
 */
void processInput(char* str, Stack* st) {
    char* accum = str;
    while(*str && *str != '\n') {
        if(*str == ' ') {
            resolveWord(accum, str - accum, st);
            accum = str + 1;
        }
        ++str;
    }
    resolveWord(accum, str - accum, st); // Resolve o que faltar
}


void printVal(Value top) {
    switch (top.type)
    {
        case Double: printf("%g", top.decimal); break;
        case Int: printf("%d", top.integer); break;
        case Char: printf("%c", top.character); break;
        case String: printf("\"%s\"", top.string); break;
    }
}


/**
 * \brief Imprime a stack fornecida para o ecrã. 
 * 
 * De notar que esta função retira todos os elementos da mesma, resultando
 * uma stack vazia.
 * 
 * @param st   A stack a imprimir
 */
void printStack(Stack* st) {
    if(!isEmpty(st)) {
        Value top = pop(st);

        printStack(st);
        printVal(top);
    }
}

/**
 * \brief Imprime a stack fornecida para o ecrã e muda de linha. 
 * 
 * De notar que esta função retira todos os elementos da mesma, resultando
 * uma stack vazia.
 * 
 * @param st   A stack a imprimir
 */
void printStackLine(Stack* st) {
    printStack(st);
    printf("\n");
}