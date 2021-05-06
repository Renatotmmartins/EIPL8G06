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
	st->previous = NULL;
	return st;
}

/**
 * \brief Verifica se o pointer aponta para uma stack vazia.
 * 
 * @param s  O pointer para o qual se quer averiguar se a stack é vazia
 * @return   1 (true) se a stack for vazia, 0 (false) se for
 */
bool isEmpty(Stack s) {
	return s->previous == NULL;
}

/**
 * \brief Devolve o valor do tamanho da stack (número de elementos na stack)
 * 
 * @param s  O pointer da stack
 * @return   O valor do tamanho da stack
 */
int length(Stack s){
    int r=0;

    while(isEmpty(s)==0){
        r++;
        s=s->previous;
    }
    return r;
}

/**
 * \brief Insere o valor especificado na stack fornecida.
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor a inserir na stack
 */
void push(Stack s, Value value) {
	Stack a = malloc(sizeof(struct stack));

    *a = *s;
    s->value = value;
    s->previous = a;
}

/**
 * \brief Remove o elemento do topo da stack, retornando o valor 
 * desse mesmo elemento.
 * 
 * @param s     O pointer para a stack
 * @return 	O elemento removido do topo da stack
 */
Value pop(Stack s) {
	Stack previous = s->previous;
	Value top = s->value;
	*s = *previous;

    if(previous != NULL)
	    free(previous);

	return top;
}

/**
 * \brief Retorna o valor que está no fundo da stack
 * 
 * @param st A stack dada
 * @return Valor no fundo da stack
 */
Value popBottom(Stack st) {
    while (!isEmpty(st->previous))
        st = st->previous;

    st->previous = NULL;
    return st->value;
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
    Stack st = empty();
    push(st, v);
    return fromStack(st);
}

/**
 * \brief Devolve o n-ésimo elemento da stack (0 é o topo da stack)
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor do n-ésimo elemento
 */
Value getElement(Stack st, int n){

    while (n--)
        st=st->previous;

    return st->value;
}

/**
 * \brief Faz uma cópia da stack dada
 * 
 * @param st A stack dada
 * @return Uma stack igual à stack original
 */
Stack clone(Stack st)
{
    if (isEmpty(st))
        return empty();

    Stack copy = clone(st->previous);
    push(copy, deepCopy(st->value));
    return copy;
}

/**
 * \brief "Junta" duas stacks
 * 
 * @param a Primeira stack dada
 * @param b Segunda stack dada
 * @return Stack que resulta da junção das duas stacks dadas inicialmente
 */
Stack merge(Stack a, Stack b) {
    //Se uma stack for representada Tail---Head:
    //{ 1, 2, 3 } + {4, 5, 6} = { 1, 2, 3, 4, 5, 6 }
    //Ou seja, a cabeça do resultado é a cabeça da segunda stack passada
    if (isEmpty(b)) {
        free(b);
        return a;
    }

    Stack last = b;

    while (!isEmpty(last->previous))
        last = last->previous;

    free(last->previous);
    last->previous = a;
    return b;
}

/**
 * \brief Enquanto o topo da stack for vazio, elimina as células vazias
 * 
 * @param st Stack dada
 */
void disposeStack(Stack st) {
    while (!isEmpty(st))
        eraseTop(st);

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
 * \brief Converte uma string para tipo #Value.
 *
 * @param str  a string
 * @return     a string convertida para #Value.
 */
Value fromString(char* str){
    Value val;

    val.type = String;

    //free(str);
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
 * \brief Cria um value a partir de um bloco com a forma de string
 * @param block bloco dado
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
    int size = length(v.array);
    char* str = (char*) malloc(sizeof(char) * (size + 1));


    int i;
    for(i = 0; i < size; i++) {
        Value temp = v.array->value;
        v.array = v.array->previous;
        str[size - i - 1] = temp.character;
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
        case Array:     free(v.array);      break;
        case Block:     free(v.block);      break;
        default:                            break;

    }
}