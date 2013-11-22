/* Instruction.h
 * CS388-HPCA
 *
 *  Author: David Zemon
 *   Email: david@stlswedespeed.com
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <stdint.h>

enum instructionType_t {LONG, SHORT, INSTRUCTION_TYPES};

class Instruction {
    public:
        Instruction (const uint32_t instruction);
        ~Instruction ();

        static instructionType_t getInstrType (const uint32_t instruction);

    protected:
        uint32_t m_instruction;
        uint8_t m_opcode;
        uint32_t m_opcodeMask;
        uint32_t m_op1;
        uint32_t m_op1Mask;
        uint8_t m_op2;
        uint32_t m_op2Mask;
        uint8_t m_op3;
        uint32_t m_op3Mask;
};

#endif /* INSTRUCTION_H_ */
