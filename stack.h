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
 * \brief Representa os diferentes tipos de dados que é possível armazenar
 * na stack
 */
typedef enum dataType {
	Double, //!< Valor Fracionário
	Int, //!< Valor Inteiro
	Char, //!< Caracter
	String //!< Texto
} DataType; //! Representa a enum DataType


/**
 * \brief Representa os diferentes valores que é possível armazenar
 * na stack
 */
typedef struct value {
/**
 * \brief Representa o tipo de dados armazenado
 */
	DataType type;
	/**
 	 * \brief Guarda os diferentes tipos possíveis de armazenar
 	 */
	union {
		int integer; //!< Valor Inteiro
		double decimal; //!< Valor Fracionário
		char character; //!< Caracter
		char* string; //!< Texto
	};

} Value; //! Representa a enum DataType


/**
 * \brief Representa uma stack (pilha), estrutura de dados LIFO, que pode ser
 * acedida pelas funções definidas abaixo.
 */
typedef struct stack {
	/*! Apontador para o valor seguinte na pilha (esta é
	    representada como uma lista ligada).*/
	struct stack* previous;

	/*! O valor armazenado na lista ligada.*/
	Value value;
} Stack; //! Representa a Stack


Stack empty();

bool isEmpty(Stack* s);

void push(Stack* s, Value value);

Value pop(Stack* s);

Value fromInteger(int i);

Value fromDecimal(double d);

Value fromCharacter(char ch);

Value fromString(char* str);
#endif