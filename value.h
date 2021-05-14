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

Value fromInteger(long long);

Value fromDecimal(double);

Value fromCharacter(char);

Value fromString(char*);

Value fromBlock(char* block, long long length);

Value deepCopy(Value);

void printVal(Value val);
#endif