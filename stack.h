/**
 * @file contém a definição de uma stack (pilha).
 */

#ifndef STACK_H
/*! Include guard */
#define STACK_H


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
typedef struct stack

{
	/*! Apontador para o valor seguinte na pilha (esta é
	    representada como uma lista ligada).*/
	struct stack* previous;

	/*! O valor armazenado na lista ligada.*/
	int value;
} Stack;


Stack empty();


bool isEmpty(Stack* s);


void push(Stack* s, int value);


int pop(Stack* s);
#endif
