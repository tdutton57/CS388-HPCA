/**
 * @file    CDC7600_Exceptions.h
 * @project CDC7600
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#ifndef CDC7600_EXCEPTIONS_H_
#define CDC7600_EXCEPTIONS_H_

#include <string>

typedef enum _cdc7600_exception {
    NOT_IMPLEMENTED_YET,
    INVALID_INPUT,
    FUNCTIONAL_UNIT_NOT_READY,
    FILE_DOES_NOT_EXIST,
    INVALID_INSTRUCTION_OPERAND,
    TOTAL_CDC7600_EXCEPTIONS
} cdc7600_exception;

extern const std::string CDC7600_EXCEPTION_STRINGS[TOTAL_CDC7600_EXCEPTIONS];

#endif /* CDC7600_EXCEPTIONS_H_ */
