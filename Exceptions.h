/**
 * @file    Exceptions.h
 * @project CDC7600
 *
 * @author  David Zemon, Tiffani Dutton
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

typedef enum _cdc7600_exception {
    NOT_IMPLEMENTED_YET,
    INVALID_INPUT,
    FUNCTIONAL_UNIT_NOT_READY,
    FILE_DOES_NOT_EXIST,
    INVALID_INSTRUCTION_OPERAND,
    INSTRUCTION_STACK_OOR, /** Instruction stack out-of-range */
    FUNCTIONAL_UNIT_NONEXISTANT,
    CDC6600_NO_FUNCTIONAL_UNIT,
    PROGRAM_MEM_NOT_LOADED,
    NONEXISTANT_PROC,
    INSTRUCTION_PARSER_ERROR,
    TOTAL_CDC7600_EXCEPTIONS
} cdc7600_exception;

extern const std::string EXCEPTION_STRINGS[TOTAL_CDC7600_EXCEPTIONS];

#endif /*EXCEPTIONS_H_ */
