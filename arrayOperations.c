/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre arrays
 */

#include <string.h>
#include "arrayOperations.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Procura pelo padrão fornecido na string dada, desalocando os argumentos
 *        fornecidos.
 * 
 *        Retorna o índice no qual o padrão inicia na string dada, ou -1 
 *        caso o padrão não exista na string.
 *
 * @param st  A string dada (sob a forma de #Value)
 *
 * @param pat O padrão a procurar na string dada (sob a forma de #Value)
 *
 * @return    O #Value com um inteiro correspondente ao índice da 
 *  1ª ocorrência na string, -1 se o padrão não for uma substring da string dada
 */
Value substrAndDispose(Value st, Value pat) {
    Value res = substr(st, pat);
    //Desaloca os valores
    disposeValue(st);
    disposeValue(pat);

    return res;
}

/**
 * \brief Procura pelo padrão fornecido na string dada. 
 * 
 *        Retorna o índice no qual o padrão inicia na string dada, ou -1 
 *        caso o padrão não exista na string.
 *
 * @param st  A string dada (sob a forma de #Value)
 *
 * @param pat O padrão a procurar na string dada (sob a forma de #Value)
 *
 * @return    O #Value com um inteiro correspondente ao índice da 
 *  1ª ocorrência na string, -1 se o padrão não for uma substring da string dada
 */
Value substr(Value st, Value pat) {
    //Obtém as strings através dos Values
    char *str = toString(st), *pattern = toString(pat);

    printf("%s %s\n", str, pattern);

    int res = -1;
    int i;
    for(i = 0; str[i]; i++) {
        int j;

        //Calcula até onde é que as strings coincidem
        for(j = 0; str[i + j] && str[i + j] == pattern[j]; j++);

        //Se chegamos ao fim do padrão então encontramos uma correspondência
        if(!pattern[j]) {
            res = i;
            break;
        }
    }

    free(str);
    free(pattern);

    return fromInteger(res);
}

/**
 * \brief Copia o prefixo da string dada com o tamanho dado para outra string
 *
 * @param src    A string de origem
 *
 * @param dest   A string de destino
 *  
 * @param length O comprimento do prefixo a copiar
 */
void copyPrefix(char* src, char* dest, int length) {
    int i;
    for(i = 0; i < length; i++)
        dest[i] = src[i];

    //Coloca o null terminator no fim da string
    dest[length] = '\0';
}

/**
 * \brief Separa uma string pela substring dada, retornando uma array de strings
 *
 * @param s      A string a separar (sob a forma de #Value)
 *
 * @param pat    O padrão a usar para separar a string (sob a forma de #Value)
 *
 * @return        O #Value correspondendo a uma array (stack) de strings
 */
Value separateBySubstr(Value s, Value pat) {
    Stack st = empty();

    //Obtém as strings a partir dos Values
    char* or, *str = toString(s);
    char* pattern = toString(pat);
    or = str;

    int pat_length = strlen(pattern);
    char* current = pattern; //posicao atual no padrao
    char* accum = str; //último split (no início nao houve splits)

    while (*str) {
        if (*str == *current)
            current++;
        else
            current = pattern;

        if (*current == '\0') {
            if (str - pat_length > accum) {
                char temp = *(str - pat_length + 1); //Guarda o caracter a seguir ao split
                *(str - pat_length + 1) = '\0';      //e substitui por um null terminator
                push(st, fromString(accum));         //para poder chamar fromString.
                *(str - pat_length + 1) = temp;      //Depois é só substituir de volta.
            }
            current = pattern;
            accum = str + 1;
        }

        str++;
    }

    if (str > accum) //ultimo push (se for preciso...)
        push(st, fromString(accum));

    //Libertar valores, pq não vão ser reutilizados
    disposeValue(s);
    disposeValue(pat);

    free(or);
    free(pattern);

    return fromStack(st);
}

/**
 * \brief Separa a stack st pelo índice x a contar de cima
 * @param st      A stack a separar; é alterada para ter tamanho x
 * @param x       O índice pelo o qual se vai separar
 * @return       Retorna a stack de baixo
 */
Stack split(Stack st, int x){
   
   while(x>0){
       st=st->previous;
       x--;
    }
    Stack a=empty();
    *a=*st;
    st->previous=NULL;
    return a;
}