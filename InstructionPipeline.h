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
#include "Exceptions.h"

/*
 * @brief   This class represents the Instruction Pipeline for the CDC6000
 *          series of processors
 */
class InstructionPipeline {

    public:
        typedef enum _cdc_proc_t {
            CDC6600,
            CDC7600,
            CDC_PROCS
        } cdc_proc_t;

    protected:
        class InstructionStack {
            public:
                InstructionStack () :
                        m_maxSize(0) {
                }

                void setMaxSize (const unsigned int maxSize) {
                    m_maxSize = maxSize;
                }

                void clear ();

                bool contains (const unsigned int pc);

                Instruction retrieve (const unsigned int pc);

                void push_back (
                        const std::vector<std::pair<unsigned int, Instruction> > &word);

            protected:
                unsigned int m_maxSize;
                std::list<std::vector<std::pair<unsigned int, Instruction> > > m_stack;
        };

    public:
        InstructionPipeline ();
        ~InstructionPipeline ();
        void reset ();

        void setProcessor (const cdc_proc_t proc);

        void load (Instruction &instr, unsigned int &currentWord, unsigned int &bitOffset);

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

        bool isNewWord () {
            return m_newWord;
        }

        unsigned int size () const;

        std::string getInstrStr () const;

    protected:
        void pushToStack (const unsigned int pc);

    protected:
        std::vector<Instruction> m_instrMem;
        unsigned int m_prevPC;
        unsigned int m_wordStartClock;
        InstructionStack m_stack;
        bool m_newWord;

        unsigned int m_defaultDelay;
        unsigned int m_pcIncAddTime;
        unsigned int m_memAccessAddTime;
        unsigned int m_instrStackDelayTime;
};

#endif /* INSTRUCTIONPIPELINE_H_ */
