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
 * \brief Verifica se o caracter especificado existe na string no tamanho indicado
 * @param str     A string
 * @param length  O tamanho da string
 * @param c       O caracter
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro ou 0 caso seja falso)
 */
bool contains(char* str, long long length, char c) {
    while (length--) {
        if (*str == c)
            return true;
        str++;
    }
    return false;
}

/**
 * \brief Lê um input e retorna um value com o valor do input
 * @param str input dado
 * @param st o state do programa
 * @return value que foi dado no input
 */
Value readValue(char* str, long long length, State* st) {
    if ('A' <= *str && *str <= 'Z') //variável
        return deepCopy(st->variables[*str-'A']);
    if (contains(str, length, '.')) //double (contém um separador decimal)
        return fromDecimal(atof(str));
    else
        return fromInteger(atoi(str)); //inteiro
}

/**
 * \brief Verifica se o operador existe. Caso exista chama o operador e caso não exista retorna 0 (false).
 * @param str Contém o operador
 * @param st O state a preencher
 * @return Um inteiro que simboliza o valor lógico (1 caso seja verdadeiro ou 0 caso seja falso)
 */
bool operation(char* str, long long length, State* st) {
    switch (*str) { JUMP_TABLE }
    return false;
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

    for ((*str)++; escape || **str != '"'; (*str)++) {
        if (escape) {
            push(read, fromCharacter(getControlChar(**str)));
            escape = false;
        } else if (**str == '\\')
            escape = true;
        else
            push(read, fromCharacter(**str));
    }
    
    Value r = fromStack(read);
    r.type = String;
    return r;
}

/**
 * \brief converte uma string para uma array, retornada sob a forma de um Value
 *
 * @param s     O estado atual
 * @param str   A string
 */
Value readArray(State* s, char** str) {
    (*str)++;
    Stack current = s->stack; //guarda a stack atual
    s->stack = empty();
    processInput(str, s); //chama processInput recursivamente com uma stack vazia
    Value r = fromStack(s->stack);
    s->stack = current; //recupera a stack
    return r;
}

/**
 * \brief Avança o pointer dado até ao fim do bloco
 *
 * @param str Pointer dado
 */
void readBlock(char** str) {
    for ((*str)++; **str != '}' && **str != ']'; (*str)++) {
        switch (**str) {
            case '"':
            //dispose do valor lido (só queremos mudar a posição de *str) TODO: otimizar
            disposeValue(readString(str));
            break;

            case '[':
            case '{':
            //chamada recursiva em vez de contar os parênteses e as chavetas
            readBlock(str);
            break;
        }
    }
}

/**
 * \brief Processa a palavra fornecida, preenchendo a stack dada ou efetuando a operação descrita.
 * 
 * @param str       A string correspondente à palavra
 * @param length    O tamanho da palavra
 * @param st        O state a preencherstr
 */
void resolveWord(char* str, long long length, State* st)
{
    if (length <= 0)
        return;
    
    if(atof(str) != 0 || !operation(str, length, st))
        push(st->stack, readValue(str, length, st));
}

/**
 * \brief Processa a string fornecida, e preenche a stack dada, efetuando todas as operações descritas na string.
 * 
 * @param str   A string correspondente ao input
 * @param st    O state a preencher
 */
void processInput(char** str, State* st) {
    char *aux, *accum = *str;
    while(**str && **str != '\n' && **str != ']') {

        //printStack(st->stack);
        //printf(" | %s\n", *str);

        switch (**str) {
            case ' ': //Value simples ou operador
            resolveWord(accum, *str - accum, st);
            break;

            case '"': //String
            push(st->stack, readString(str));
            break;

            case '[': //Array
            push(st->stack, readArray(st, str));
            break;

            case '{': //Bloco
            aux = *str;     //guarda o início do bloco
            readBlock(str); //avança até ao fim do bloco
            //calcula o tamanho (dado como a diferença entre as posições das chavetas)
            push(st->stack, fromBlock(aux + 1, *str - aux));
            break;

            default:    (*str)++;   continue; //nao foi lido um símbolo
        }
        accum = *str + 1; //foi lido um símbolo
        (*str)++;
    }
    resolveWord(accum, *str - accum, st); // Resolve o que faltar
}