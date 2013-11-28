/**
 * @file    Instruction.h
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <stdint.h>
#include <string>

#define NULL_OPERAND    -1

/**
 * @brief   An instance of this class represents one of many instructions
 *          executed by the CDC6600 or CDC7600
 */
class Instruction {
    public:
        typedef enum _type {
            SHORT, LONG
        } type;

        typedef enum _opcode_t {
            INC = 050, MULF = 040, ADDF = 030, SUBF = 031
        } opcode_t;

        typedef enum _register_t {
            x0,
            x1,
            x2,
            x3,
            x4,
            x5,
            x6,
            x7,
            a0,
            a1,
            a2,
            a3,
            a4,
            a5,
            a6,
            a7,
            b0,
            b1,
            b2,
            b3,
            b4,
            b5,
            b6,
            b7
        } register_t;

        class FlexableOp {
            public:
                FlexableOp () :
                        m_type(0), m_reg(x0), m_imm(0) {
                }

                FlexableOp (const Instruction::register_t reg) :
                        m_type(0), m_reg(reg), m_imm(0) {
                }

                FlexableOp (const int imm) :
                        m_type(1), m_reg(x0), m_imm(imm) {
                }

                const void* get () const {
                    if (m_type)
                        return (void *) &m_imm;
                    else
                        return (void *) &m_reg;
                }

                bool getType () const {
                    return m_type;
                }

            protected:
                bool m_type;
                Instruction::register_t m_reg;
                int m_imm;
        };

    public:
        Instruction () :
                m_description(""), m_type(SHORT), m_wordNum(0), m_opcode(
                        (opcode_t) 0), m_op1(x0), m_op2(0), m_op3(0) {
        }

        /**
         * @brief   Constructor to create an instance of the class instruction
         */
        Instruction (const std::string description, const opcode_t opcode,
                const register_t op1, const FlexableOp &op2,
                const FlexableOp &op3);

//        static instructionType_t getInstrType (const uint32_t instruction);

        /**
         * @brief   Function to set the word number for this instruction
         */
        void setWordNum (const uint32_t wordNum) {
            m_wordNum = wordNum;
        }

        /**
         * @brief   Function to return description string
         */
        std::string getDescription () const {
            return m_description;
        }

        /**
         * @brief   Function to return the type of instruction
         */
        Instruction::type getType () const {
            return m_type;
        }

        /**
         * @brief   Function to return the word number for the instruction
         */
        uint32_t getWordNum () const {
            return m_wordNum;
        }

        /*
         * @brief   Function to return the opcode of the instruction
         * @return  The opcode of the instruction is returned
         */
        opcode_t getOpcode () const {
            return m_opcode;
        }

        /**
         * @brief   Accessor function to return the instruction's first operand
         */
        uint32_t getOp1 () const {
            return m_op1;
        }

        /**
         * @brief   Accessor function to return the type of the instruction
         */
        const void* getOp2 () const {
            return m_op2.get();
        }

        /**
         * @brief   Accessor function to return the type of the instruction
         */
        const void* getOp3 () const {
            return m_op3.get();
        }

        /**
         * @brief   Function that determines whether two instructions are equal
         */
        bool operator== (const Instruction &rhs);

        /**
         * @brief   Check function to determine whether two instructions are not
         *          equal
         */
        bool operator!= (Instruction &rhs);

    protected:
        /**
         * @brief   Determine if an instruction is a long or short instruction
         */
        static Instruction::type getInstrType (const opcode_t opcode);

    protected:
        std::string m_description;

        Instruction::type m_type;  // Type of instruction: LONG/SHORT
        uint32_t m_wordNum;  // Which word does this instruction belong to
        opcode_t m_opcode;

        // Instruction operands
        register_t m_op1;
        FlexableOp m_op2;
        FlexableOp m_op3;
};

#endif /* INSTRUCTION_H_ */
