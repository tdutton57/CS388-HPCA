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
#define OUT_FILENAME    "CDC7600_output2.csv"
#define OUTPUT          OUT_FILE
#endif

/**
 * Program 1 instructions
 * Y = A*X^2 + B
 */
Instruction program1[] = {
    Instruction("Fetch x", Instruction::INC, Instruction::a1, 42, 0),
    Instruction("Fetch A", Instruction::INC, Instruction::a2, 42, 0),
    Instruction("Form x^2", Instruction::MULF, Instruction::x0, Instruction::x1, Instruction::x1),
    Instruction("Form Ax^2", Instruction::MULF, Instruction::x6, Instruction::x0, Instruction::x2),
    Instruction("Fetch B", Instruction::INC, Instruction::a3, 42, 0),
    Instruction("Form Y", Instruction::ADDF, Instruction::x7, Instruction::x6, Instruction::x3),
    Instruction("Store Y", Instruction::INC, Instruction::a7, 42, 0) };

/**
 * Program 2 instructions
 * Y = A*X^2 + B*X + c
 */
Instruction program2[] = {
    Instruction("Fetch x", Instruction::INC, Instruction::a1, 1, 0),
    Instruction("Fetch A", Instruction::INC, Instruction::a2, 2, 0),
    Instruction("Form x^2", Instruction::MULF, Instruction::x0, Instruction::x1, Instruction::x1),
    Instruction("Form Ax^2", Instruction::MULF, Instruction::x6, Instruction::x0, Instruction::x2),
    Instruction("Fetch B", Instruction::INC, Instruction::a3, 3, 0),
    Instruction("Fetch C", Instruction::INC, Instruction::a4, 4, 0),
    Instruction("Form BX", Instruction::MULF, Instruction::x3, Instruction::x1, Instruction::x1),
    Instruction("Form AX^2 + BX", Instruction::ADDF, Instruction::x5,  Instruction::x6, Instruction::x3),
    Instruction("Form Y", Instruction::ADDF, Instruction::x7, Instruction::x5, Instruction::x4),
    Instruction("Store Y", Instruction::INC, Instruction::a7, 5, 0) };

/**
 * Program 3 instructions
 * Y = A*X^2 + B*X + C (X and Y are vectors)
 */
Instruction program3[] = {
    // Preparation for looping!
    // Values N, A, B, and C are all stored in a vector and can be fetched
    // in order
    // Two main things must be done:
    //   1) Fetch the loop counter (b0 = N)
    //   2) Fetch all constants (b1 = A, b2 = B, b3 = C)
    //   3) Fetch the starting address of each vector (a1 = &(X[0]) - 1, a7 = &(Y[0]) - 1)
    Instruction("Fetch N", Instruction::INC, Instruction::a1, Instruction::a1, 42),
    Instruction("MOV N", Instruction::INC, Instruction::b0, Instruction::x1, 0),
    Instruction("Fetch A", Instruction::INC, Instruction::a1, Instruction::a1, 1),
    Instruction("MOV A", Instruction::INC, Instruction::b1, Instruction::x2, 0),
    Instruction("Fetch B", Instruction::INC, Instruction::a1, Instruction::a1, 1),
    Instruction("MOV B", Instruction::INC, Instruction::b2, Instruction::x2, 0),
    Instruction("Fetch C", Instruction::INC, Instruction::a1, Instruction::a1, 1),
    Instruction("MOV C", Instruction::INC, Instruction::b3, Instruction::x2, 0),
    Instruction("Fetch &(X[0] - 1)", Instruction::INC, Instruction::a1, Instruction::a2, 99),
    Instruction("Init &(Y[0]) - 1", Instruction::INC, Instruction::a7, Instruction::a7, 199),

    // Loop internals
    Instruction("Fetch X[i]", Instruction::INC, Instruction::a1, Instruction::a1, 1),
    Instruction("Form X[i]^2", Instruction::MULF, Instruction::x0, Instruction::x1, Instruction::x1),
    Instruction("MOV A", Instruction::INC, Instruction::x2, Instruction::b1, 0),
    Instruction("Form A*X[i]^2", Instruction::MULF, Instruction::x3, Instruction::x0, Instruction::x2),
    Instruction("MOV B", Instruction::INC, Instruction::x2, Instruction::b2, 0),
    Instruction("Form B*X[i]", Instruction::MULF, Instruction::x4, Instruction::x1, Instruction::x2),
    Instruction("Form A*X[i]^2 + B*X[i]", Instruction::ADDF, Instruction::x3, Instruction::x3, Instruction::x4),
    Instruction("MOV C", Instruction::INC, Instruction::x2, Instruction::b3, 0),
    Instruction("Form Y[i]", Instruction::ADDF, Instruction::x7, Instruction::x2, Instruction::x3),
    Instruction("Decrement N", Instruction::INC, Instruction::b0, Instruction::b0, -1),
    Instruction("Store Y[i]", Instruction::INC, Instruction::a7, Instruction::a7, 1),
    Instruction("Loop", Instruction::BNQ, Instruction::b0, Instruction::b7, 10) };

Instruction* readFile (int argc, char *argv[]);

#endif /* CDC7600_MAIN_H_ */
