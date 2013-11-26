/**
 * @file    cdc7600_main.h
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#ifndef CDC7600_MAIN_H_
#define CDC7600_MAIN_H_

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <list>
#include "Instruction.h"
#include "CDC7600.h"

// Program instructions
const Instruction program1[] = {
        Instruction(FETCH, NULL_OPERAND, 1, NULL_OPERAND),
        Instruction(FETCH, NULL_OPERAND, 2, NULL_OPERAND),
        Instruction(MULF, 1, 1, 2)
};

const uint8_t WORD_LENGTH= 8;

/**
 * @brief   Reads a file, 8 bytes at a time
 */
std::list<uint64_t> readFile (int argc, char *argv[]);


#endif /* CDC7600_MAIN_H_ */
