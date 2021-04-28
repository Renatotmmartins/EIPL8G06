/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre arrays
 */

#include <string.h>
#include "arrayOperations.h"

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
    char *str = st.string, *pattern = pat.string;
    int res = -1;
    int i;
    for(i = 0; str[i]; i++) {
        int j;

        //Calcula até onde é que as strings coincidem
        for(j = i; str[i + j] && str[i + j] == pattern[j]; j++);

        //Se chegamos ao fim do padrão então encontramos uma correspondência
        if(!pattern[j]) {
            res = i;
            break;
        }
    }

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
    char* str = s.string;
    char* pattern = pat.string;

    int length = strlen(pattern);
    Value v = substr(fromString(str), fromString(pattern));;

    //Variável temporária para armazenar substrings de str
    char* temp = malloc(sizeof(char) * strlen(str));

    //Enquanto houver string e houver correspondência
    while(v.integer != -1 && *str) {
        //Copia apenas a substring
        copyPrefix(str, temp, v.integer);
        //Insere na stack uma cópia dessa substring
        push(st, deepCopy(fromString(temp)));
        //Atualiza o apontador para a próxima posição de interesse
        str += v.integer + length;
    }

    return fromStack(st);
}