/**
 * @file    CDC7600.h
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#ifndef CDC7600_H_
#define CDC7600_H_

#include <iostream>
#include <list>
#include <algorithm>
#include <sstream>
#include <string>
#include "Instruction.h"
#include "FunctionalUnit.h"
#include "InstructionPipeline.h"

#define CDC7600_REGISTER_BANK_SIZE    8
#define CDC7600_WORDS_PER_LONGWORD    2
#define CDC7600_MEM_ACCESS_TIME       4
#define CDC7600_OUTPUT_DELIM          ','

typedef unsigned int Register;

class CDC7600 {
    public:
        CDC7600 (std::ostream *out, const Instruction program[],
                const unsigned int instrCount);

        ~CDC7600 ();

        int run ();

        int runLoop (const int n);

        void reset ();

    protected:
        void initOutput ();

        FunctionalUnit* getFunctionalUnit (const Instruction *instr);
        std::list<Register> getRegisterOperands (Instruction *instr) const;

        unsigned int getResultsAvailable (std::list<Register> *registers);

        void runInstruction (Instruction *instr);

    protected:
        std::ostream *m_out;

        InstructionPipeline m_instrMem;
        unsigned int m_pc;

        unsigned int m_clock;
        unsigned int m_issue;
        unsigned int m_issueWord;
        std::vector<FunctionalUnit> m_funcUnits;

        Register m_Rx[CDC7600_REGISTER_BANK_SIZE];
        Register m_Ra[CDC7600_REGISTER_BANK_SIZE];
        Register m_Rb[CDC7600_REGISTER_BANK_SIZE];
};

#endif /* CDC7600_H_ */
