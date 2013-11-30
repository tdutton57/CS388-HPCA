/**
 * @file    InstructionPipeline.h
 * @project CDC7600
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#ifndef INSTRUCTIONPIPELINE_H_
#define INSTRUCTIONPIPELINE_H_

#include <cstddef>
#include <vector>
#include <utility>
#include <list>
#include "Instruction.h"
#include "CDC7600_Exceptions.h"

/*
 * @brief   This class represents the Instruction Pipeline for the CDC6000
 *          series of processors
 */
class InstructionPipeline {
    protected:
        class InstructionStack {
            public:
                void clear ();

                bool contains (const unsigned int pc);

                Instruction retrieve (const unsigned int pc);

                void push_back (
                        const std::vector<std::pair<unsigned int, Instruction> > &word);

            protected:
                std::list<std::vector<std::pair<unsigned int, Instruction> > > m_stack;
        };

    public:
        InstructionPipeline ();
        ~InstructionPipeline ();
        void clear ();

        void load (Instruction &instr);

        void load (Instruction program[], const unsigned int instrCount);

        /**
         * @brief   Retrieve the next instruction and the delay required
         *
         * @param   pc          Address of the instruction to be retrieved
         * @param   *nextInstr  Address where the next instruction should be
         *                      placed
         *
         * @return  Returns the delay (in clock cycles) required to retrieve
         *          the requested instruction
         */
        uint8_t readInstr (const unsigned int pc, Instruction* &nextInstr);

        unsigned int size () const;

        std::string getInstrStr () const;

    protected:
        void pushToStack (const unsigned int pc);

    protected:
        std::vector<Instruction> m_instrMem;
        unsigned int m_prevPC;
        InstructionStack m_stack;
};

#endif /* INSTRUCTIONPIPELINE_H_ */
