/**
 * @file    Instruction.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#include "Instruction.h"

// TODO: Learn the binary instruction format of the CDC6000 series computers
#define LONG_OPCODE_MASK    -1
#define LONG_OP1_MASK       -1
#define LONG_OP1_SHIFT      0
#define LONG_OP2_MASK       -1
#define LONG_OP2_SHIFT      0

#define SHORT_OPCODE_MASK    -1
#define SHORT_OP1_MASK       -1
#define SHORT_OP1_SHIFT      0
#define SHORT_OP2_MASK       -1
#define SHORT_OP2_SHIFT      0
#define SHORT_OP3_MASK       -1
#define SHORT_OP3_SHIFT      0

Instruction::Instruction (const uint32_t instruction) {
    m_type = Instruction::getInstrType(instruction);

    switch (this->m_type) {
        case LONG:
            m_opcode = (opcode_t) (instruction & LONG_OPCODE_MASK);
            m_op1 = (instruction & LONG_OP1_MASK) >> LONG_OP1_SHIFT;
            m_op2 = (instruction & LONG_OP2_MASK) >> LONG_OP2_SHIFT;
            break;
        case SHORT:
            m_opcode = (opcode_t) (instruction & SHORT_OPCODE_MASK);
            m_op1 = (instruction & SHORT_OP1_MASK) >> SHORT_OP1_SHIFT;
            m_op2 = (instruction & SHORT_OP2_MASK) >> SHORT_OP2_SHIFT;
            m_op3 = (instruction & SHORT_OP3_MASK) >> SHORT_OP3_SHIFT;
            break;
        default:
            throw "Oh crap... how did this happen?";
    }
}

Instruction::Instruction (const opcode_t opcode, const uint32_t op1,
        const uint8_t op2, const uint8_t op3) {
    m_type = Instruction::getInstrType(opcode);
    m_opcode = opcode;
    m_op1 = op1;
    m_op2 = op2;
    m_op3 = op3;

}

instructionType_t Instruction::getInstrType (const uint32_t instruction) {
    // TODO: Determine what instructions are long and short
    if (0) {
        return LONG;
    } else
        return SHORT;
}

instructionType_t Instruction::getInstrType (const opcode_t opcode) {
    return LONG;  // TODO: Determine if opcode is long or short instruction
}

uint32_t Instruction::getOp1 () const {
    return m_op1;
}

uint8_t Instruction::getOp2 () const {
    return m_op2;
}

uint8_t Instruction::getOp3 () const {
    return m_op3;
}

uint8_t Instruction::getOpcode () const {
    return m_opcode;
}

instructionType_t Instruction::getType () const {
    return m_type;
}

bool Instruction::operator== (const Instruction &rhs) {
    return m_type == rhs.m_type && m_opcode == rhs.m_opcode
            && m_op1 == rhs.m_op1 && m_op2 == rhs.m_op2 && m_op3 == rhs.m_op3;
}

bool Instruction::operator!= (const Instruction &rhs) {
    return !(*this == rhs);
}
