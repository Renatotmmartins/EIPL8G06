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


/**
 * \brief Verifica se o caracter fornecido é um algarismo.
 * 
 * @param ch O caracter fornecido
 * @return   Se for um algarismo, 1, senão, 0
 */
bool isNumeric(char ch) {
    return (ch - '0' >= 0 && ch - '0' <= 9);
}


/**
 * \brief Calcula o número de operandos exigidos pela operação definida pelo
 * caracter dado.
 * 
 * @param ch O caracter fornecido
 * @return   O número de operandos exigidos pela respetiva operação (-1 caso
 *           o caracter não codifique nenhuma operação)
 */
int numberOperands (char ch) {
    /*
        Esta função armazena todos os operandos numa array de strings, tal que
        se um operando necessita de x operandos, então encontra-se no índice x
        da dita array.

        Assim, para calcular o número de operandos de um dado caracter basta
        encontrar o índice da string onde este pertence. 
    */
    char operandList[3][10] = {"_;l\\@","()~ifcs$","+-/*&|^%#"};

    for (int i = 0; i < 3; i++)
        for (int j = 0; operandList[i][j]; j++)
            if (operandList[i][j] == ch)
                return i;

    return -1;
}


/**
 * \brief Executa a operação definida pelo caracter dado, a qual exige dois operandos,
 * x e y, na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param x  O primeiro operando
 * @param y  O segundo operando
 * @param ch O caracter que define a operação a executar
 */
void twoOperands(Stack* st, Value x, Value y, char ch) {

    switch (ch) {
        case '+': push(st, sum(x, y));          break;  // Soma de 2 valores
        case '-': push(st, subtract(x, y));     break;  // Subtração de 2 valores
        case '*': push(st, multiply(x, y));     break;  // Multiplicação de 2 valores
        case '/': push(st, divide(x, y));       break;  // Divisão de 2 valores
        case '%': push(st, module(x, y));       break;  // Resto da divisão inteira
        case '#': push(st, exponentiate(x, y)); break;  // Exponenciação (x elevado a y)
        case '&': push(st, AND(x, y));          break;  // X e Y
        case '|': push(st, OR(x, y));           break;  // X ou Y
        case '^': push(st, XOR(x, y));          break;  // X xor Y
    }
}

/**
 * \brief Executa a operação definida pelo caracter dado, a qual exige um operando x,
 * na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param x  O operando
 * @param ch O caracter que define a operação a executar
 */
void oneOperand(Stack* st, Value x, char ch) {
    switch(ch) {
        case '(': push(st, decrement(x));               break;  //subtrair 1
        case ')': push(st, increment(x));               break;  //adicionar 1
        case '~': push(st, negate(x));                  break;  //negacao lógica (bitwise)
        case 'i': push(st, convertToInt(x));            break;  //converte para inteiro
        case 'f': push(st, convertToDouble(x));         break;  //converte para floating point precisao dupla
        case 'c': push(st, convertToChar(x));           break;  //converte para caracter (ascii)
        case 's': push(st, convertToString(x));         break;  //converte para string (array de caracteres)
        case '$': push(st, getElement(st, x.integer));  break;  //copia o n-ésimo elemento da stack para o topo
    }
}

/**
* \brief Executa a operação definida pelo caracter dado, a qual não exige nenhum operando,
* na stack fornecida.
*
* @param st A stack onde executar a operação
* @param ch O caracter que define a operação a executar
*/

void zeroOperands(Stack* st, char ch) {
    switch (ch) {
        case ';':   pop (st);           break;
        case 'l':   readLine (st);      break;
        case '\\':  rotateTop(st, 2);   break;
        case '@':   rotateTop(st, 3);   break;
        case '_':   duplicate(st);      break;
    }
}

/**
 * \brief Executa a operação definida pelo caracter dado na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param ch O caracter que define a operação a executar
 */
void operation (Stack* st, char ch) {
    int op = numberOperands(ch);
    Value operands[op];
    
    /* Retira da stack todos os operandos necessários */
    for(int i = 0; i < op; i++)
        operands[i] = pop(st);

    switch(op) {
        case 0: zeroOperands(st, ch);                           break;
        case 1: oneOperand(st, operands[0], ch);                break;
        case 2: twoOperands(st, operands[1], operands[0], ch);  break;
    }
}

/**
 * \brief Procura o caracter especificado na string.
 * 
 * @param str       A string
 * @param length    O tamanho da string
 * @param c         O caracter a procurar
 * @return          1 se o caracter pertencer à string, 0 se não
 */
bool contains(char* str, int length, char c)
{
    for (int i = 0; i < length; i++)
        if (str[i] == c)
            return true;

    return false;
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

    if (length == 1 && numberOperands(*str) != -1) {  //operador
        operation(st, *str);
        return;
    }

    Value v;

    if(length == 1 && !isNumeric(*str)) {
        v.type = Char;
        v.character = *str;                     //char
    }
    else if (contains(str, length, '.')) {           //double
        v.type = Double;
        v.decimal = atof(str);
    }
    else {                                      //int
        v.type = Int;
        v.integer = atoi(str);
    }

    push(st, v);
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

        //bool empty = isEmpty(st);

        printStack(st);

        //if(!empty)
            //printf(" ");

        switch (top.type) {
            case Double:    printf("%g", top.decimal);      break;
            case Int:       printf("%d", top.integer);      break;
            case Char:      printf("%c", top.character);    break;
            case String:    printf("\"%s\"", top.string);   break;
        }
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
