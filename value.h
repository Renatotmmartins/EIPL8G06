/**
 * @file contém a declaração das funções relacionadas
 * com Values
 */

//! Include guard
#ifndef VALUE_H
//! Include guard
#define VALUE_H


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

Value fromInteger(long long);

Value fromDecimal(double);

Value fromCharacter(char);

Value fromString(char*);

Value fromBlock(char* block, int length);

Value deepCopy(Value);

void printVal(Value val);