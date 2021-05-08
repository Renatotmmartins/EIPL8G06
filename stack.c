/**
 * @file contém a implementação de uma stack (pilha)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

/**
 * \brief A stack vazia.
 *
 * @return   Um objeto do tipo Stack sem nenhum elemento
 */
Stack empty() {
	Stack st = malloc(sizeof(struct stack));
    st->size = 0;
    st->capacity = 128;
    st->values = malloc(sizeof(Value) * st->capacity);
	return st;
}

/**
 * \brief Verifica se o pointer aponta para uma stack vazia.
 * 
 * @param s  O pointer para o qual se quer averiguar se a stack é vazia
 * @return   1 (true) se a stack for vazia, 0 (false) se for
 */
bool isEmpty(Stack s) {
	return s->size == 0;
}

/**
 * \brief Devolve o valor do tamanho da stack (número de elementos na stack)
 * 
 * @param s  O pointer da stack
 * @return   O valor do tamanho da stack
 */
int length(Stack s){
    return s->size;
}

/**
 * \brief Insere o valor especificado na stack fornecida.
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor a inserir na stack
 */
void push(Stack s, Value value) {
	/*Stack a = malloc(sizeof(struct stack));
    *a = *s;
    s->value = value;
    s->previous = a;*/
    if(s->size == s->capacity) {
        s->capacity *= 2;
        s->values = realloc(s->values, sizeof(Value) * s->capacity);
    }
    s->values[s->size++] = value;
}

/**
 * \brief Remove o elemento do topo da stack, retornando o valor 
 * desse mesmo elemento.
 * 
 * @param s     O pointer para a stack
 * @return 	O elemento removido do topo da stack
 */
Value pop(Stack s) {
	return s->values[--(s->size)];
}

/**
 * \brief Retorna o valor que está no fundo da stack
 * 
 * @param st A stack dada
 * @return Valor no fundo da stack
 */
Value popBottom(Stack st) {
    Value res = st->values[0];
    int i;
    for(i = 1; i < st->size; i++) {
        st->values[i - 1] = st->values[i];
    }
    st->size--;
    return res;
}
/**
 * \brief Apaga o valor que está no topo da stack
 * @param st A stack dada
 */
void eraseTop(Stack st) {
    disposeValue(pop(st));
}

/**
 * \brief Converte um #Value para outro que armazena uma stack
 * 
 *  @param v     O #Value a converter
 *  @return      O #Value que guarda a stack
 */
Value convertToStack(Value v) {
    if (v.type < String) {
        Stack st = empty();
        push(st, v);
        return fromStack(st);
    }
    //v.type = Array ???
    return v;
}

/**
 * \brief Devolve o n-ésimo elemento da stack (0 é o topo da stack)
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor do n-ésimo elemento
 */
Value getElement(Stack st, int n){
    return st->values[st->size - 1 - n];
}

/**
 * \brief Faz uma cópia da stack dada
 * 
 * @param st A stack dada
 * @return Uma stack igual à stack original
 */
Stack clone(Stack st)
{
    Stack res = malloc(sizeof(struct stack));
    res->size = st->size;
    res->capacity = st->capacity;
    res->values = malloc(sizeof(Value) * st->capacity);
    memcpy(res->values, st->values, sizeof(Value) * st->size);
    return res;
}

/**
 * \brief "Junta" duas stacks
 * 
 * @param a Primeira stack dada
 * @param b Segunda stack dada
 * @return Stack que resulta da junção das duas stacks dadas inicialmente
 */
Stack merge(Stack a, Stack b) {
    for (int i = 0; i < b->size; i++)
        push(a, b->values[i]);

    free(b->values);
    free(b);
    return a;
}

/**
 * \brief Enquanto o topo da stack for vazio, elimina as células vazias
 * 
 * @param st Stack dada
 */
void disposeStack(Stack st) {
    //int l = length(st);
    while (!isEmpty(st))
        eraseTop(st);
    //if(l > 1000)
        free(st->values);
    free(st);
}

/**
 * \brief Converte um inteiro para tipo #Value.
 *
 * @param i  o inteiro
 * @return   o inteiro convertido para #Value.
 */
Value fromInteger(long long i){
    Value val;

    val.type=Int;
    val.integer=i;

    return val;
}


/**
 * \brief Converte um double para tipo #Value.
 *
 * @param d  o double
 * @return   o double convertido para #Value.
 */
Value fromDecimal(double d){
    Value val;

    val.type=Double;
    val.decimal=d;

    return val;
}

/**
 * \brief Converte um caracter para tipo #Value.
 *
 * @param ch  o caracter
 * @return    o caracter convertido para #Value.
 */
Value fromCharacter(char ch){
    Value val;

    val.type=Char;
    val.character=ch;

    return val;
}

/**
 * \brief Converte uma string para tipo #Value. Não liberta a str.
 *
 * @param str  a string. Não é libertada.
 * @return     a string convertida para #Value.
 */
Value fromString(char* str){
    Value val;

    val.type = String;

    val.array = stringToStack(str);
    return val;
}

/**
 * \brief Converte uma string para uma stack
 *
 * @param str  a string dada
 * @return     a stack resultante
 */
Stack stringToStack(char* str) {
    Stack st = empty();
    //char* og = str;
    while (*str)
        push(st, fromCharacter(*(str++)));

    return st;
}

/**
 * \brief Converte uma stack para tipo #Value.
 *
 * @param st   a stack
 * @return     a stack convertida para #Value.
 */
Value fromStack(Stack st) {
    Value val;

    val.type = Array;
    val.array = st;

    return val;
}

/**
 * \brief Cria um value a partir de um bloco com a forma de string. A string não é libertada.
 * @param block bloco dado. Não é libertado.
 * @param length Tamanho da string + 1
 * @return Value criado a partir de um bloco com a forma da string
 */

Value fromBlock(char* block, int length) {
    Value val;

    val.type = Block;
    val.block = malloc( length * sizeof (char));
    memcpy(val.block,block,(length-1) * sizeof (char));
    val.block [(length-1)] = '\0';
    return val;
}

/**
 * \brief Copia valor que esteja inicialmente na stack
 * @param v Valor inicialmente dado
 * @return Valor copiado na sua nova localização.
 */
Value deepCopy(Value v) {
    Value copy = v;

    if (v.type == Array || v.type == String)
        copy.array = clone(v.array);

    else if (v.type == Block)
        copy.block = strdup(v.block);

    return copy;
}

/**
 * \brief Converte um #Value para string
 * 
 * @param v Value dado que vai ser convertido para string
 * @return A string obtida a partir do #Value
 */
char* toString(Value v) {
    if(v.type == Char) {
        char* str = (char*) malloc(sizeof(char) * 2);
        str[0] = v.character;
        str[1] = '\0';
        return str;
    }
    int size = length(v.array);
   // printf("%d\n", size);
    char* str = (char*) malloc(sizeof(char) * (size + 1));
    str[0] = '\0';
    int i;
    //printStackLine(v.array);
    for(i = 0; i < size; i++) {
        //printf("VALOR %d ", v.array->values[i].type);
        str[i] = v.array->values[i].character;
        //printf("\n");
    }
    
    str[size] = '\0';
    return str;
}

/**
 * \brief Desaloca valor que esteja presente na memória
 * @param v
 */
void disposeValue(Value v) {
    switch (v.type) {
        case String:
        case Array:     disposeStack(v.array);      break;
        case Block:     free(v.block);      break;
        default:                            break;

    }
}


/**
 * \brief Efetua print do valor dado
 * @param top Valor a ser dado print
 */

void printVal(Value top) {
    switch (top.type) {
        case Double:    printf("%g", top.decimal);      break;
        case Int:       printf("%lld", top.integer);      break;
        case Char:      printf("%c", top.character);    break;
        case String:
        case Array:     printStack(top.array);          break;
        case Block:     printf("{%s}", top.block);       break;
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
    for (int i = 0; i < st->size; i++)
        printVal(st->values[i]);

    /*if (!isEmpty(st)) {
        Value top = pop(st);
        printStack(st);
        printVal(top);
        disposeValue(top);
    }*/

    /*reverseStack(st);
    while (!isEmpty(st)) {
        Value a = pop(st);
        printVal(a);
        disposeValue(a);
    }*/
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