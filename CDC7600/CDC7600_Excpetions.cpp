/**
 * @file    CDC7600_Excpetions.cpp
 * @project CDC7600
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#include "CDC7600_Exceptions.h"

const std::string CDC7600_EXCEPTION_STRINGS[TOTAL_CDC7600_EXCEPTIONS] = {
        "Sorry, that hasn't been implemented yet!",
        "Invalid input!",
        "Functional unit not ready!",
        "Error: File cannot be opened",
        "Instruction operand is not valid",
        "Out of range: Instruction stack",
        "A functional unit was requested which doesn't exist"
    	"Your functional unit does not have a number associated with it"};
