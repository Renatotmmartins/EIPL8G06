/**
 * 
 * @file contém a implementação das funções usadas para processar o input e 
 * preencher a stack fornecida
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"

/**
 * \brief Verifica se o operador existe. Caso exista chama o operador e caso não exista retorna 0 (false).
 * @param str Contém o operador
 * @param st O state a preencher
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro ou 0 caso seja falso)
 */
bool operation(char* str, State* st) {
    //! Expansão da JumpTable para Switch
    #define ENTRY(a,b,c) case a: PUSH_##c(st->stack, b(POP_##c )); return true;
    switch (*str) { JUMP_TABLE }
    #undef ENTRY

    return false;
}

/**
 * \brief Lê um input e retorna um value com o valor do input
 * @param str input dado
 * @param st o state do programa
 * @return value que foi dado no input
 */
Value readValue(char* str, State* st) {
    if ('A' <= *str && *str <= 'Z') //variável
        return st->variables[*str-'A'];
        
    if (strchr(str, '.') == NULL) //double (tem um separador decimal)
        return fromInteger(atoi(str));
    else
        return fromDecimal(atof(str)); //inteiro
}

/**
 * \brief Converte um caracter escapado para o respetivo caracter de controlo
 * @param c Caracter dado
 * @return Caracter de controlo
 */

char getControlChar(char c) {
    switch (c) {
        case 'n':   return '\n';
        case 't':   return '\t';
        case '0':   return '\0'; //isto vai dar porcaria, não vai?
        case '\"':  return '\"';
        case '\\':  return '\\';
        default:    return '\\';
        //se nao foi detetado um caracter de controlo assumimos
        //que se pretendia escrever o próprio backslash
    }
}

/**
 * \brief converte uma string para uma Stack de caracteres
 * @param str String dada
 * @return Stack de caracteres
 */
Value readString(char** str) {
    //mete *str a apontar para a aspa que fecha
    Stack read = empty();
    bool escape = false;

    while (escape || **str != '"') {
        if (escape) {
            push(read, fromCharacter(getControlChar(**str)));
            escape = false;
        }
        else if (**str == '\\')
            escape = true;
        else
            push(read, fromCharacter(**str));
            
        (*str)++;
    }
    
    return fromStack(read);
}

/**
 * \brief Processa a palavra fornecida, preenchendo a stack dada ou efetuando a operação descrita.
 * 
 * @param str       A string correspondente à palavra
 * @param length    O tamanho da palavra
 * @param st        O state a preencher
 */
void resolveWord(char* str, int length, State* st)
{
    if (length <= 0)
        return;

    if(!operation(str, st))
        push(st->stack, readValue(str, st));
}


/**
 * \brief Processa a string fornecida, e preenche a stack dada, efetuando todas as operações descritas na string.
 * 
 * @param str   A string correspondente ao input
 * @param st    O state a preencher
 */
void processInput(char** str, State* st) {
    char* accum = *str;
    Stack current;
    while(**str && **str != '\n' && **str != ']') {
        switch (**str)
        {
            case ' ':
            resolveWord(accum, *str - accum, st);
            accum = *str + 1;
            break;

            case '"':
            (*str)++;
            push(st->stack, readString(str));
            accum = *str + 1;
            break;

            case '[':
            current = st->stack; //guarda a stack atual
            st->stack = empty();
            (*str)++;
            processInput(str, st); //chama processInput recursivamente com uma stack vazia
            push(current, fromStack(st->stack));
            st->stack = current; //recupera a stack
            accum = *str + 1;
            break;
        }
        (*str)++;
    }
    resolveWord(accum, *str - accum, st); // Resolve o que faltar
}

/**
 * \brief Efetua print do valor dado
 * @param top Valor a ser dado print
 */

void printVal(Value top) {
    switch (top.type) {
        case Double:    printf("%g", top.decimal);      break;
        case Int:       printf("%d", top.integer);      break;
        case Char:      printf("%c", top.character);    break;
        case String:    printf("\"%s\"", top.string);   break;
        case Array:     printStack(top.array);          break;
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
void printStack(Stack st) {
    if(!isEmpty(st)) {
        Value top = pop(st);

        printStack(st);
        printVal(top);
        disposeValue(top);
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
void printStackLine(Stack st) {
    printStack(st);
    printf("\n");
}