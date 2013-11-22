/* Instruction.cpp
 * CS388-HPCA
 *
 *  Author: David Zemon
 *   Email: david@stlswedespeed.com
 */

#include "Instruction.h"

Instruction::Instruction (const uint32_t instruction) {
    this->OPCODE_MASK = 0x;

    this->m_instruction = instruction;
    this->m_opcode = instruction;
}

Instruction::~Instruction () {
// TODO Auto-generated destructor stub
}

static instructionType_t Instruction::getInstrType (
        const uint32_t instruction) {
    // TODO: Determine what instructions are long and short
    if (0) {
        return LONG;
    } else
        return SHORT;
}
