/**
 * @file contém a implementação das funções correspondentes às operações
 * sobre arrays
 */

#include <string.h>
#include "arrayOperations.h"
#include "blockOperations.h"
#include "logicOperations.h"
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
    char *str = toString(st);
    char *pattern = toString(pat);
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
 * \brief Auxiliar da função separateBySubstr. Parte a string fornecida
 *        pelo padrão dado (na forma de strings (char*))
 *
 * @param str      A string a separar
 *
 * @param pattern  O padrão a usar para separar a string
 *
 * @return         A array (stack) de strings
 */
Stack separateBySubstrAux(char* str, char* pattern) {
    Stack st = empty();

    int pat_length = strlen(pattern);
    char* current = pattern; //posicao atual no padrao
    char* accum = str; //último split (no início nao houve splits)

    //Enquanto não acabar o string
    while (*str) {
        if (*str == *current)
            current++;
        else
            current = pattern;

        //Se tivermos encontrado uma ocorrência do padrão
        if (*current == '\0') {
            if (str - pat_length >= accum) {
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

    if (*accum) //ultimo push se for preciso
        push(st, fromString(accum));

    return st;
}

/**
 * \brief Separa uma string pela substring dada, retornando uma array de strings
 *
 * @param s      A string a separar (sob a forma de #Value)
 *
 * @param pat    O padrão a usar para separar a string (sob a forma de #Value)
 *
 * @return       O #Value correspondendo a uma array (stack) de strings
 */
Value separateBySubstr(Value s, Value pat) {
    //Obtém as strings a partir dos Values
    char *str = toString(s);
    char* pattern = toString(pat);

    Stack r = separateBySubstrAux(str, pattern);1

    //Libertar valores, pq não vão ser reutilizados
    disposeValue(s);
    disposeValue(pat);

    //Libertar strings
    free(str);
    free(pattern);

    return fromStack(r);
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

/**
 * \brief Ordena o array dado de acordo com o bloco fornecido
 * @param array   O array a ordenar
 * @param x       O bloco que é usado para comparar elementos
 * @return        O array ordenado
 */
Value sort(State* s, Value array, Value block) {
    int size = length(array.array);
    //Chama o merge sort
    //Esta função auxiliar é necessária pois é preciso saber de antemão
    //o tamanho da stack.
    return fromStack(mergeSort(s, array.array, block, size));
}

/**
 * \brief Função que inverte a stack
 * @param s Stack fornecida e que irá ser invertida
 */

void reverseStack(Stack s) {
    Stack st = empty();
    while(!isEmpty(s)) {
        push(st, pop(s));
    }

    *s = *st;
    free(st);
}

/**
 * \brief Ordena o array dado de acordo com o bloco fornecido
 * @param s       O estado do programa
 * @param l       O primeiro array a juntar
 * @param r       O segundo array a juntar
 * @param block   O bloco que é usado para comparar elementos
 * @return        O array ordenado
 */
Stack mergeStacks(State* s, Stack l, Stack r, Value block) {
    reverseStack(l);
    reverseStack(r);
    Stack res = empty();
    //Enquanto nenhuma stack é vazia
    while(!isEmpty(l) && !isEmpty(r)) {
        Stack s1 = empty();
        Stack s2 = empty();
        //Value v1 = l->value, v2 = r->value;
        push(s1, deepCopy(l->value));
        push(s2, deepCopy(r->value));

        Stack st = s->stack;
        s->stack = s1;
        Value v1 = execute(s, s->stack, block);
        s->stack = s2;
        Value v2 = execute(s, s->stack, block);

        s->stack = st;
        //Se a condição executada retorna verdadeiro, então l < r
        if(isTrue(isLess(v1,v2))) {
            /*printVal(v1);
            printf("<");
            printVal(v2);*/
            push(res, pop(l));
        } else {
            /*printVal(v1);
            printf(">");
            printVal(v2);*/
            push(res, pop(r));
        }
        //printf("\n");
        disposeStack(s1);
        disposeStack(s2);
    }
    

    //Insere na stack res todos os elementos das duas stacks que ainda não foram
    //inseridos (apenas tem efeito para uma das stacks)
    reverseStack(l);
    reverseStack(r);
    res = merge(res, l);
    res = merge(res, r);

    return res;
}

/**
 * \brief Ordena o array dado de acordo com o bloco fornecido
 * @param s       O estado do programa
 * @param array   O array a ordenar
 * @param x       O bloco que é usado para comparar elementos
 * @return        O array ordenado
 */
Stack mergeSort(State* s, Stack st, Value block, int n) {
    //Caso base: a stack já está ordenada
    /*printf("NOVA ITEREACAO\n");
    printStack(deepCopy(fromStack(st)).array);
    printf("%d\n", n);
    printf("------------------------\n");*/
    if(n <= 1)
        return st;
    //Parte a stack em duas
    Stack firstHalf = split(st, (n + 1) / 2);

    //Ordena as duas metades
    firstHalf = mergeSort(s, firstHalf, block, n - ((n + 1) / 2));
    st = mergeSort(s, st, block, (n + 1) / 2);

    /*printStack(deepCopy(fromStack(st)).array);
    printf(" ");
    printStack(deepCopy(fromStack(firstHalf)).array);
    printf("\n");*/
    //Junta as metades ordenadas para uma nova stack ordenada
    return mergeStacks(s, st, firstHalf, block);
}