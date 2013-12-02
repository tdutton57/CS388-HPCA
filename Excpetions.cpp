/**
 * @file   Excpetions.cpp
 * @project CDC7600
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#include "Exceptions.h"

const std::string EXCEPTION_STRINGS[TOTAL_CDC7600_EXCEPTIONS] = {
        "Sorry, that hasn't been implemented yet!",
        "Invalid input!",
        "Functional unit not ready!",
        "Error: File cannot be opened",
        "Instruction operand is not valid",
        "Out of range: Instruction stack",
        "A functional unit was requested which doesn't exist"
    	"Your functional unit does not have a number associated with it",
        "Program memory has not been loaded",
        "That processor isn't real. Learn things please",
        "The instruction parser can't parse that"};
