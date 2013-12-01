/**
 * @file    Instruction.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#include "Instruction.h"

Instruction::opcode_t Instruction::parseOpcode (const std::string opcode) {
    if ("ADDF" == opcode)
        return Instruction::ADDF;
    else if ("SUBF" == opcode)
        return Instruction::SUBF;
    else if ("MULF" == opcode)
        return Instruction::MULF;
    else if ("INC" == opcode)
        return Instruction::INC;
    else if ("BNQ" == opcode)
        return Instruction::BNQ;
    else
        throw INSTRUCTION_PARSER_ERROR;
}

Instruction::register_t Instruction::parseReg (const std::string op1) {
    char bank = op1[0];
    unsigned int reg = op1[1] - '0';
    register_t startingReg;

    switch (bank) {
        case 'a':
            startingReg = Instruction::a0;
            break;
        case 'b':
            startingReg = Instruction::b0;
            break;
        case 'x':
            startingReg = Instruction::x0;
            break;
        default:
            throw INSTRUCTION_PARSER_ERROR;
    }

    return static_cast<Instruction::register_t>(startingReg + reg);
}
Instruction::FlexableOp Instruction::parseFlexOps (
        const std::string flexOp) {
    if ('#' == flexOp[0]) {
        std::string temp = flexOp.substr(1);
        return FlexableOp(std::atoi(temp.c_str()));
    }
    else
        return parseReg(flexOp);
}

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

std::string Instruction::getInstrStr () const {
    std::stringstream s;

    s << m_op1 << "=" << m_op2;

    switch (m_opcode) {
        case Instruction::ADDF:
        case Instruction::INC:
            s << '+';
            break;
        case Instruction::MULF:
            s << '*';
            break;
        case Instruction::SUBF:
            s << '-';
            break;
        default:
            s << '?';
    }

    s << m_op3;

    return s.str();
}

// Operator==
bool Instruction::operator== (const Instruction &rhs) {
    bool retVal = true;

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

bool Instruction::getOpType (const uint8_t operand) const {
    switch (operand) {
        case 2:
            return m_op2.getType();
            break;
        case 3:
            return m_op3.getType();
            break;
        default:
            throw INVALID_INSTRUCTION_OPERAND;
    }
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

std::ostream& operator<< (std::ostream& s, const Instruction::register_t reg) {
    if (Instruction::x0 <= reg && reg <= Instruction::x7)
        s << 'x' << static_cast<unsigned int>(reg - Instruction::x0);
    else if (Instruction::a0 <= reg && reg <= Instruction::a7)
        s << 'a' << static_cast<unsigned int>(reg - Instruction::a0);
    else if (Instruction::b0 <= reg && reg <= Instruction::b7)
        s << 'b' << static_cast<unsigned int>(reg - Instruction::b0);

    return s;
}

std::ostream& operator<< (std::ostream& s, const Instruction::FlexableOp op) {
    if (op.getType())
        return s << *static_cast<const Instruction::register_t *>(op.get());
    else
        return s << 'k';
}
