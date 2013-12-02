/**
 * @file    CDC6000.h
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#ifndef CDC6000_H_
#define CDC6000_H_

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <cstdio>
#include "Instruction.h"
#include "FunctionalUnit.h"
#include "InstructionPipeline.h"
#include "Exceptions.h"

#define CDC6000_REGISTER_BANK_SIZE    8
#define CDC6000_WORDS_PER_LONGWORD    2
#define CDC7600_MEM_ACCESS_TIME       4
#define CDC6600_MEM_ACCESS_TIME       5
#define CDC6000_OUTPUT_DELIM          ','

#define CDC6600_NUM_MULF              2
#define CDC6600_NUM_INC               2
#define CDC6600_NUM_BOOL              1
#define CDC6600_NUM_JMP               1
#define CDC6600_NUM_SHIFT             1
#define CDC6600_NUM_ADDF              1
#define CDC6600_NUM_ADDL              1
#define CDC6600_NUM_DIVF              1

/**
 * @brief: This class represents an instance of the CDC7600
 */
class CDC6000 {
    protected:
        class Register {
            public:
                Register () :
                        m_readReady(0), m_lock(0) {
                }

                void reset () {
                    m_readReady = m_lock = 0;
                }

                unsigned int getLock () const {
                    return m_lock;
                }

                void setLock (const unsigned int lock) {
                    m_lock = lock;
                }

                unsigned int getReadReady () const {
                    return m_readReady;
                }

                void setReadReady (const unsigned int readReady) {
                    m_readReady = readReady;
                }

            protected:
                unsigned int m_readReady;  // Value ready to be read at this clock cycle
                unsigned int m_lock;  // Lock this register from being written until a specific clock cycle
        };

    public:
        /**
         * @brief   Constructor which initializes the functional units
         *          and program memory
         *
         * @param   out
         */
        CDC6000 ();

        /**
         * @brief   Destructor to delete an instance of the CDC7600
         */
        virtual ~CDC6000 ();

        virtual void init (std::ostream *out, Instruction program[],
                const unsigned int instrCount);

        /**
         * @brief   Runs the set of instructions once
         */
        void run ();

        /**
         * @brief   Runs a set of instructions n times. This is used
         *          for when there is a branch statement (as in program 3).
         *          When there are branch statements, the instructions need
         *          need to be run a certain number of times.
         *
         * @param   n The number of iterations for running the instructions
         */
        void run (const unsigned int n);

        /**
         * @brief   This will reset the CDC7600 so that it is ready to read
         *          a new set of instructions. It will reset the program
         *          counter, the clock cycles, issue time, the functional units,
         *          and all registers
         */
        virtual void reset ();

    protected:
        /**
         * @brief       Simulate execution of a single instruction with output
         *
         * @detailed    This is called by the run function in order to run each
         *              individual instruction. This function determines the
         *              clock cycles for the instruction issue, start, result,
         *              unit ready, fetch and store. It calls the printInstrInfo
         *              to print this information into the time table.
         *
         * @param       *instr A pointer to the instruction that will be run
         */
        void runInstruction (Instruction *instr);

        /**
         * @brief   This function initializes the data in the first row
         *          of the time table. This row includes the column headers
         *          which include the Word#, Instruction, Description, Length,
         *          Issue, Start, Result, and so forth.
         */
        void initOutput ();

        /**
         * @brief   Prints a row information pertaining to a particular
         *          instruction into the time table
         *
         * @param   *instr A pointer to the instruction
         * @param   *funcUnit A pointer to the functional unit required for
         *          executing the instruction
         * @param   start The number of clock cycles after the program is run
         *          for when this instruction is started
         * @param   result The number of clock cycles after the program is run
         *          for when the result of this instruction is obtained
         * @param   fetchStr If the instruction is a FETCH type instruction,
         *          then this number will represent the number of clock cycles
         *          after the program is run for when the result of this
         *          instruction is fetched
         * @param   storeStr If the instruction is a STORE type instruction,
         *          then this number will represent the number of clock cycles
         *          after the program is run for when the result of this
         *          instruction is stored
         */
        void printInstrInfo (const Instruction *instr,
                const FunctionalUnit *funcUnit, const unsigned int start,
                const unsigned int result, const std::string fetchStr,
                const std::string storeStr);

        /**
         * @brief   Returns the functional unit used for this instruction
         */
        virtual FunctionalUnit* getFunctionalUnit (
                const Instruction *instr) = 0;

        /**
         * @brief   Returns the list of registers that could delay the
         *          time to start executing the instruction
         * @param   *instr A pointer to the instruction for which we want
         *          to return its dependency registers
         */
        std::list<Instruction::register_t> getDependencyRegisters (
                const Instruction *instr) const;

        const CDC6000::Register getRegister (
                const Instruction::register_t reg) const;

        CDC6000::Register* getRegisterP (const Instruction::register_t reg);

        unsigned int latestDependencyTime (
                const std::list<Instruction::register_t> &registers);

    protected:
        std::ostream *m_out;
        bool m_firstRun;

        InstructionPipeline m_instrMem;
        unsigned int m_pc;
        unsigned int m_newWordDelay;
        unsigned int m_memAccessTime;

        unsigned int m_clock;
        unsigned int m_issue;
        unsigned int m_wordStart;

        CDC6000::Register m_Rx[CDC6000_REGISTER_BANK_SIZE];
        CDC6000::Register m_Ra[CDC6000_REGISTER_BANK_SIZE];
        CDC6000::Register m_Rb[CDC6000_REGISTER_BANK_SIZE];
};

class CDC7600: public CDC6000 {
    public:
        CDC7600 () :
                CDC6000() {
            m_memAccessTime = CDC7600_MEM_ACCESS_TIME;
        }

        void init (std::ostream *out, Instruction program[],
                const unsigned int instrCount);

        void reset ();

        /**
         * @brief   Returns the functional unit used for this instruction
         */
        FunctionalUnit* getFunctionalUnit (const Instruction *instr);

    protected:
        std::vector<FunctionalUnit> m_funcUnits;
};

class CDC6600: public CDC6000 {
    protected:
        static unsigned int getNumFunctionalUnit (
                const FunctionalUnit::typeCDC6600 unit);
    public:
        CDC6600 () :
                CDC6000() {
            m_memAccessTime = CDC6600_MEM_ACCESS_TIME;
        }

        void init (std::ostream *out, Instruction program[],
                const unsigned int instrCount);

        void reset ();

        /**
         * @brief   Returns the functional unit used for this instruction
         */
        FunctionalUnit* getFunctionalUnit (const Instruction *instr);
    protected:
        FunctionalUnit* getReadyFunction (
                std::vector<FunctionalUnit> *functUnits);
    protected:
        std::vector<std::vector<FunctionalUnit> > m_funcUnits;
};
#endif /* CDC6000_H_ */
