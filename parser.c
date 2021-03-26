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
    char operandList[3][10] = {"","()~","+-/*&|^%#"};
    int i,j;

    for(i=0;i<3;i++) {
        for(j=0;operandList[i][j];j++) {
            if(operandList[i][j]==ch) {
                return i;
            }
        }
    }

    return 0;
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
void twoOperand(struct stack* st, int x, int y, char ch) {
    if (ch == '+') push(st,(x + y)); // Soma de 2 valores
    else if (ch == '-') push(st,(x-y)); // Subtração de 2 valores
    else if (ch == '*') push(st, (x * y)); // Multiplicação de 2 valores
    else if (ch == '/') push(st,(x / y)); // Divisão de 2 valores
    else if (ch == '%') push(st, (x % y)); // Resto da divisão inteira
    else if (ch == '#') push(st, (int)pow(x,y)); // Exponenciação (x elevado a y)
    else if (ch == '&') push(st, (x & y)); // X e Y
    else if (ch == '|') push(st, (x | y)); // X ou Y
    else if (ch == '^') push(st, (x ^ y)); // X xor Y

}

/**
 * \brief Executa a operação definida pelo caracter dado, a qual exige um operando x,
 * na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param x  O operando
 * @param ch O caracter que define a operação a executar
 */
void oneOperand(struct stack* st, int x, char ch) {
    if (ch == '(') push(st,(--x)); 
    else if (ch == ')') push(st,(++x));
    else if (ch == '~') push(st,(~x));
}

/**
 * \brief Executa a operação definida pelo caracter dado na stack fornecida.
 * 
 * @param st A stack onde executar a operação
 * @param ch O caracter que define a operação a executar
 */
void operation (struct stack* st, char ch) {
    int op,i;

    op = numberOperands(ch);
    int operands[op];
    for(i = 0; i < op; i++){
        operands[i]= pop(st);
    }
    if(op == 1){
        oneOperand(st,operands[0], ch);
    }else if(op == 2){
        twoOperand(st, operands[1], operands[0], ch);
    }
}

/**
 * \brief Processa a string fornecida, e preenche a stack dada, efetuando todas as operações descritas na string.
 * 
 * @param str   A string correspondente ao input
 * @param st    A stack a preencher
 */
void processInput(char* str, struct stack* st) {
    //O numero que esta atualmente a ser lido, e o número de caracteres desde a última inserção
    // na stack
    int currentNumber = 0, read = 0;
    while(*str != '\0') {
        if(isNumeric(*str)) {
            //Atualiza o valor atual do número
            currentNumber *= 10;
            currentNumber += *str - '0';
            ++read;
        }
        else if(*str == ' ' && read > 0) {
            //Insere o valor atual na stack
            push(st, currentNumber);           
            currentNumber = 0;
            read = 0;
        }
        else {
            //Faz a operação pedida
            operation(st, *str);
            read = 0;
        }
        ++str;
    }

    //Insere o último elemento lido na stack
    if(read > 0) {
        push(st, currentNumber);
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
void printStack(struct stack* st) {
    if(!isEmpty(st)) {
        int top = pop(st);
        printStack(st);
        printf("%d", top);
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
void printStackLine(struct stack* st) {
    printStack(st);
    printf("\n");
}
