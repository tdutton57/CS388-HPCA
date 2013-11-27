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
        Instruction(FETCH, 1, 1, NULL_OPERAND),  // Add 1 to A1; Fetch @(A1 + 1) into X1
        Instruction(FETCH, 2, 1, NULL_OPERAND),  // Add 1 to A2; Fetch @(A2 + 1) into X2
        Instruction(MULF, 1, 1, 2)
};

const uint8_t WORD_LENGTH= 8;

/**
 * @brief   Reads a file, 8 bytes at a time
 */
std::list<uint64_t> readFile (int argc, char *argv[]);


#endif /* CDC7600_MAIN_H_ */
