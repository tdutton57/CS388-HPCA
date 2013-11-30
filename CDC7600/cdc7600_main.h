/**
 * @file    cdc7600_main.h
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#ifndef CDC7600_MAIN_H_
#define CDC7600_MAIN_H_

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include "Instruction.h"
#include "CDC7600.h"
#include "CDC7600_Exceptions.h"

#define DEBUG

#ifdef DEBUG
#define OUTPUT          std::cout
#else
#define OUT_FILE        outfile
#define OUT_FILENAME    "CDC7600_output.csv"
#define OUTPUT          OUT_FILE
#endif

// Program 1 instructions
Instruction program1[] = {
        Instruction("Fetch x", Instruction::INC, Instruction::a1, 42, 0),
        Instruction("Fetch A", Instruction::INC, Instruction::a2, 42, 0),
        Instruction("Form x^2", Instruction::MULF, Instruction::x0,
                Instruction::x1, Instruction::x1),
        Instruction("Form Ax^2", Instruction::MULF, Instruction::x6,
                Instruction::x0, Instruction::x2),
        Instruction("Fetch B", Instruction::INC, Instruction::a3, 42, 0),
        Instruction("Form Y", Instruction::ADDF, Instruction::x7,
                Instruction::x6, Instruction::x3),
        Instruction("Store Y", Instruction::INC, Instruction::a7, 42, 0) };

// Program 2 instructions
Instruction program2[] = {
        Instruction("Fetch x", Instruction::INC, Instruction::a1, 1, 0),
        Instruction("Fetch A", Instruction::INC, Instruction::a2, 2, 0),
        Instruction("Form x^2", Instruction::MULF, Instruction::x0,
                Instruction::x1, Instruction::x1),
        Instruction("Form Ax^2", Instruction::MULF, Instruction::x6,
                Instruction::x0, Instruction::x2),
        Instruction("Fetch B", Instruction::INC, Instruction::a3, 3, 0),
        Instruction("Fetch C", Instruction::INC, Instruction::a4, 4, 0),
        Instruction("Form BX", Instruction::MULF, Instruction::x3,
                Instruction::x1, Instruction::x1),
        Instruction("Form AX^2 + BX", Instruction::ADDF, Instruction::x5,
                Instruction::x6, Instruction::x3),
        Instruction("Form Y", Instruction::ADDF, Instruction::x7,
                Instruction::x5, Instruction::x4),
        Instruction("Store Y", Instruction::INC, Instruction::a7, 5, 0) };

Instruction program3[] = { };

/**
 * @brief   Reads a file, 8 bytes at a time
 */
Instruction* readFile (int argc, char *argv[]);

#endif /* CDC7600_MAIN_H_ */
