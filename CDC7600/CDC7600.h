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
#include "Instruction.h"
#include "FunctionalUnit.h"

#define CDC7600_MEM_ACCESS_TIME     4
#define CDC7600_PC_INC_TIME         2
#define CDC7600_REGISTER_BANK_SIZE  8

typedef unsigned int Register;

class CDC7600 {
    public:
        CDC7600 (std::ostream *out, std::list<uint64_t> *program);

        CDC7600 (std::ostream *out, const Instruction program[],
                const int instrCount);

        ~CDC7600 ();

        int run ();

        int runLoop (const int n);

        void reset ();

    protected:
        void initOutput ();

        FunctionalUnit* getFunctionalUnit (Instruction *instr) const;
        std::list<Register> getRegisterOperands (Instruction *instr) const;

        unsigned int getResultsAvailable (std::list<Register> *registers);

        void runInstruction(Instruction *);

    protected:
        std::ostream *m_out;

        std::list<Instruction> *m_instrMem;

        unsigned int m_clock;
        unsigned int m_issue;
        unsigned int m_issueWord;

        Register m_Rx[CDC7600_REGISTER_BANK_SIZE];
        Register m_Ra[CDC7600_REGISTER_BANK_SIZE];
        Register m_Rb[CDC7600_REGISTER_BANK_SIZE];
};

#endif /* CDC7600_H_ */
