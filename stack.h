#ifndef STACK_H
#define STACK_H

/**
 *@file contém a definição de uma stack (pilha).
 */


//! Usada para distinguir semanticamente entre valor lógico 
//! verdadeiro  e valor numérico 1.
#define true 1 

//! Usada para distinguir semanticamente 0 entre valor lógico 
//! falso  e valor numérico 0.
#define false 0

//! Usada para distinguir semanticamente o tipo int entre valor lógico 
//! e valor numérico.
#define bool int

/**
 * \struct \brief Representa uma stack (pilha), estrutura de dados LIFO, que pode ser 
 * acedida pelas funções definidas abaixo.
 */
struct stack
{
	/*! Apontador para o valor seguinte na pilha (esta é
	    representada como uma lista ligada).*/
	struct stack* previous;

	/*! O valor armazenado na lista ligada.*/
	int value;
};

/**
 * \brief A stack vazia.
 */
struct stack empty();

/**
 * \brief Verifica se o pointer aponta para uma stack vazia.
 * 
 * @param s  O pointer para o qual se quer averiguar se a stack é vazia
 * @return   1 (true) se a stack for vazia, 0 (false) se for
 */
bool isEmpty(struct stack* s);

/**
 * \brief Insere o valor especificado na stack fornecida.
 * 
 *  @param s     O pointer para a stack
 *  @param value O valor a inserir na stack
 */
void push(struct stack* s, int value);


/**
 * \brief Remove o elemento do topo da stack, retornando o valor 
 * desse mesmo elemento.
 * 
 * @param s     O pointer para a stack
 */
int pop(struct stack* s);
#endif
