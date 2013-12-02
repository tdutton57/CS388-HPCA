/**
 * @file    InstructionPipeline.cpp
 * @project CDC7600
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#include "InstructionPipeline.h"

void InstructionPipeline::InstructionStack::clear () {
    m_stack.clear();
}

bool InstructionPipeline::InstructionStack::contains (const unsigned int pc) {
    std::list<std::vector<std::pair<unsigned int, Instruction> > >::const_iterator iterator;
    for (iterator = m_stack.begin(); iterator != m_stack.end(); ++iterator)
        for (unsigned int i = 0; i < iterator->size(); ++i)
            if (pc == (*iterator)[i].first)
                return true;
    return false;
}

Instruction InstructionPipeline::InstructionStack::retrieve (
        const unsigned int pc) {
    Instruction retVal;
    std::list<std::vector<std::pair<unsigned int, Instruction> > >::iterator iterator;
    for (iterator = m_stack.begin(); iterator != m_stack.end(); ++iterator)
        for (unsigned int i = 0; i < iterator->size(); ++i)
            if (pc == (*iterator)[i].first) {
                retVal = (*iterator)[i].second;
                m_stack.erase(iterator);
                push_back(*iterator);
                return retVal;
            }

    throw INSTRUCTION_STACK_OOR;
}

void InstructionPipeline::InstructionStack::push_back (
        const std::vector<std::pair<unsigned int, Instruction> > &word) {
    m_stack.push_back(word);

    if (m_maxSize < m_stack.size())
        m_stack.pop_front();
}

InstructionPipeline::InstructionPipeline () {
    m_prevPC = NULL_OPERAND;
    m_wordStartClock = 0;
    m_newWord = true;

    // Must set these later
    m_defaultDelay = -1;
    m_pcIncAddTime = -1;
    m_memAccessAddTime = -1;
    m_instrStackDelayTime = -1;
    m_stack.setMaxSize(-1);
}

InstructionPipeline::~InstructionPipeline () {
    reset();
}

void InstructionPipeline::reset () {
    m_instrMem.clear();
    m_prevPC = NULL_OPERAND;
    m_stack.clear();
    m_wordStartClock = 0;
}

void InstructionPipeline::setProcessor (const cdc_proc_t proc) {
    switch (proc) {
        case InstructionPipeline::CDC6600:
            m_defaultDelay = 1;
            m_pcIncAddTime = 1;
            m_memAccessAddTime = 2;
            m_instrStackDelayTime = 0;
            m_stack.setMaxSize(10);
            break;
        case InstructionPipeline::CDC7600:
            m_defaultDelay = 1;
            m_pcIncAddTime = 1;
            m_memAccessAddTime = 2;
            m_instrStackDelayTime = 0;
            m_stack.setMaxSize(10);
            break;
        default:
            throw NONEXISTANT_PROC;
    }
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
    uint8_t delay = m_defaultDelay;
    bool alreadyInsterted = false;

    // Grab requested instruction
    nextInstr = &(m_instrMem[pc]);

    // If the last instruction read came from a new word, turn off the signal
    m_newWord = false;

    // If this isn't the first instruction of the program, do cool things
    if ((unsigned int) NULL_OPERAND != m_prevPC) {
        Instruction *prevInstr = &(m_instrMem[m_prevPC]);  // Previous instruction

        // If the next instruction resides in a different word than the
        // current, a memory access is required
        if (prevInstr->getWordNum() != nextInstr->getWordNum()) {
            m_newWord = true;

            // If it's in the stack, it's quick
            if (m_stack.contains(pc)) {
                m_stack.retrieve(pc);
                nextInstr = &(m_instrMem[pc]);
                alreadyInsterted = true;
                delay += m_instrStackDelayTime;
            }
            // On occasion, a branch will cause a special delay where the PC is
            // modified in a way other than simple increment
            else if (prevInstr->getWordNum() > nextInstr->getWordNum())
                switch (nextInstr->getOpcode()) {
                    // TODO: Should probably figure out the extra delays due to branching
                    default:
                        break;
                }
            // Otherwise, it's slow
            else {
                delay += m_memAccessAddTime;
            }
        } else {
            // If previous instruction was a long instruction, add an extra
            // clock cycle to the delay
            if (Instruction::LONG == prevInstr->getType())
                delay += m_pcIncAddTime;
        }
    } else
        m_newWord = true;

    m_prevPC = pc;
    if (!alreadyInsterted)
        pushToStack(pc);

    return delay;
}

unsigned int InstructionPipeline::size () const {
    return m_instrMem.size();
}

std::string InstructionPipeline::getInstrStr () const {
    return "";
}

void InstructionPipeline::pushToStack (const unsigned int pc) {
    // Can only push whole 60-bit words, not individual instructions;
    // To do this, we must determine what instructions go along with the one
    // pointed to by the PC (though this would have been easier with a different
    // setup for m_instrMem, it would have made other things much more
    // difficult)
    std::vector<std::pair<unsigned int, Instruction> > word;
    unsigned int tempPC = pc;
    std::vector<Instruction>::const_iterator iterator = m_instrMem.begin();

    advance(iterator, pc);

    // Decrement the iterator to the beginning of the current instruction word
    while (0 != tempPC && iterator->getWordNum() == m_instrMem[pc].getWordNum()) {
        --iterator;
        --tempPC;
    }

    // Loop through all instructions in the current word and add them to the
    // `word` variable, which will then be loaded onto the instruction stack
    while (m_instrMem.size() > tempPC
            && iterator->getWordNum() == m_instrMem[pc].getWordNum()) {
        word.push_back(std::pair<unsigned int, Instruction>(tempPC, *iterator));
        ++tempPC;
        ++iterator;
    }

    m_stack.push_back(word);
}
