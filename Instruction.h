/**
 * @file    Instruction.h
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <stdint.h>

typedef enum _instructionType_t {
    LONG, SHORT, INSTRUCTION_TYPES
} instructionType_t;

class Instruction {
    public:
        Instruction (const uint32_t instruction);

        static instructionType_t getInstrType (const uint32_t instruction);
        uint32_t getOp1 () const;
        uint8_t getOp2 () const;
        uint8_t getOp3 () const;
        uint8_t getOpcode () const;
        instructionType_t getType () const;

    protected:
        instructionType_t m_type;
        uint8_t m_opcode;
        uint32_t m_op1;
        uint8_t m_op2;
        uint8_t m_op3;
};

#endif /* INSTRUCTION_H_ */
