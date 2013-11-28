/**
 * @file    Instruction.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon and Katie Isbell
 * @email   david@stlswedespeed.com
 */

#include "Instruction.h"

Instruction::Instruction (const std::string description,
        const Instruction::opcode_t opcode, const Instruction::register_t op1,
        const FlexableOp &op2, const FlexableOp &op3) {
    m_description = description;

    m_wordNum = 0;  // Initially set to zero until calculated at a later time
    m_opcode = opcode;
    m_op1 = op1;
    m_op2 = op2;
    m_op3 = op3;

    // Determine the type of instruction (LONG/SHORT) based on the opcode
    m_type = getInstrType(m_opcode);

}

// Operator==
bool Instruction::operator== (const Instruction &rhs) {
    bool retVal = true;

//     m_op2 == rhs.m_op2 && m_op3 == rhs.m_op3;

    // Check the instruction type, opcode, and first operand
    retVal &= m_type == rhs.m_type && m_opcode == rhs.m_opcode
            && m_op1 == rhs.m_op1;

    // Check that the second and third operands are both of the same type
    retVal &= m_op2.getType() && rhs.m_op2.getType();
    retVal &= m_op3.getType() && rhs.m_op3.getType();

    // Check that the second and third operands are the same values
    if (m_op2.getType()) {
        int lhs2 = *((int *) (m_op2.get()));
        int rhs2 = *((int *) (rhs.m_op2.get()));
        retVal &= lhs2 == rhs2;
    } else {
        Instruction::register_t lhs2 =
                *((Instruction::register_t *) (m_op2.get()));
        Instruction::register_t rhs2 =
                *((Instruction::register_t *) (rhs.m_op2.get()));
        retVal &= lhs2 == rhs2;
    }
    if (m_op3.getType()) {
        int lhs3 = *((int *) (m_op3.get()));
        int rhs3 = *((int *) (rhs.m_op3.get()));
        retVal &= lhs3 == rhs3;
    } else {
        Instruction::register_t lhs3 =
                *((Instruction::register_t *) (m_op3.get()));
        Instruction::register_t rhs3 =
                *((Instruction::register_t *) (rhs.m_op3.get()));
        retVal &= lhs3 == rhs3;
    }

    return retVal;
}

//Operator!=
bool Instruction::operator!= (Instruction &rhs) {
    return !(*this == rhs);
}

Instruction::type Instruction::getInstrType (const opcode_t opcode) {
    if (opcode == INC || opcode == INC)
        return LONG;
    else
        return SHORT;
}
