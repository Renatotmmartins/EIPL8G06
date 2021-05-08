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
	String, //!< Texto
	Array, //!< Array
	Block, //!< Bloco
} DataType;

//! O tipo de dados usado para representar s stack
struct stack;

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
		long long integer; //!< Valor Inteiro
		double decimal; //!< Valor Fracionário
		char character; //!< Caracter
		char* block; //!< Bloco
		struct stack* array; //!< Array
	};

} Value;


/**
 * \brief Representa uma stack (pilha), estrutura de dados LIFO, que pode ser
 * acedida pelas funções definidas abaixo.
 */
typedef struct stack {
	//! A array de valores armazenados
	Value* values;
	//! O número de valores guardados
	int size;
	//! O tamanho da array
	int capacity;
} * Stack;

/**
 * \brief Representa o estado atual do programa, ou seja, as variáveis e a stack
 */
typedef struct state{
	//! A stack
	Stack stack;
	//! O array das variáveis
	Value variables[26];
} State;

Stack empty();

bool isEmpty(Stack);

int length(Stack);

void push(Stack, Value);

Value pop(Stack);

Value popBottom(Stack);

void eraseTop(Stack);

Value getElement(Stack, int);

Stack clone(Stack);

Stack merge(Stack, Stack);

void disposeStack(Stack);


Value convertToStack(Value v);

Value fromInteger(long long);

Value fromDecimal(double);

Value fromCharacter(char);

Value fromString(char*);

Stack stringToStack(char* str);

Value fromStack(Stack);

Value fromBlock(char* block, int length);

Value deepCopy(Value);

void disposeValue(Value);

char* toString(Value v);

void printVal(Value val);

void printStack(Stack st);

void printStackLine(Stack st);

#endif