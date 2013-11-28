/**
 * @file    InstructionPipeline.cpp
 * @project CDC7600
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#include "InstructionPipeline.h"

#define DEFAULT_DELAY               1
#define PC_INC_ADD_TIME             1
#define MEM_ACCESS_ADD_TIME         2

InstructionPipeline::InstructionPipeline () {
    m_prevPC = NULL_OPERAND;
}

InstructionPipeline::~InstructionPipeline () {
    clear();
}

void InstructionPipeline::clear () {
    m_instrMem.clear();
    m_prevPC = NULL_OPERAND;
}

void InstructionPipeline::load (Instruction &instr) {
    static unsigned int currentWord = 0;
    static unsigned int bitOffset = 0;

    // Determine which word of instruction memory this instruction will be
    // loaded into
    if (Instruction::SHORT == instr.getType()) {
        // Short instruction; It can always be loaded into the current word
        instr.setWordNum(currentWord);
        bitOffset += 15;
    } else if (Instruction::LONG == instr.getType() && 30 >= bitOffset) {
        // Long instruction; We must have at least 30 bits of space
        instr.setWordNum(currentWord);
        bitOffset += 30;
    } else {
        // It must be a long instruction that wouldn't fit in the current word;
        // Increment the current word, set the word num for the instruction, and
        // set the bitOffset to 30
        ++currentWord;
        instr.setWordNum(currentWord);
        bitOffset = 30;
    }

    // If adding the new instruction filled up the current word, increment it
    // and reset the bitoffset
    if (60 == bitOffset) {
        ++currentWord;
        bitOffset = 0;
    }

    m_instrMem.push_back(instr);
}

void InstructionPipeline::load (Instruction program[],
        const unsigned int instrCount) {
    for (unsigned int i = 0; i < instrCount; ++i)
        load(program[i]);
}

uint8_t InstructionPipeline::readInstr (const unsigned int pc,
        Instruction* &nextInstr) {
    uint8_t delay = DEFAULT_DELAY;

    Instruction *prevInstr = &(m_instrMem[m_prevPC]);  // Previous instruction
    nextInstr = &(m_instrMem[pc]);  // Requested instruction

    // Calculate delay
    if ((unsigned int) NULL_OPERAND != m_prevPC) {
        // In case of a branch, do something WEIRD
        if (prevInstr->getWordNum() > nextInstr->getWordNum())
            ;  // TODO: Determine delay due to PC "increment" (not really inc)
        else {
            // If previous instruction was a long instruction, add an extra
            // clock cycle to the delay
            if (Instruction::LONG == prevInstr->getType())
                delay += PC_INC_ADD_TIME;

            // If the next instruction resides in a different word than the
            // current, a memory access is required
            if (prevInstr->getWordNum() != nextInstr->getWordNum())
                delay += MEM_ACCESS_ADD_TIME;
        }
    }

    return delay;
}

unsigned int InstructionPipeline::size () const {
    return m_instrMem.size();
}

std::string InstructionPipeline::getInstrStr () const {
    return "";
}
