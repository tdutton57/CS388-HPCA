/**
 * @file    CDC7600.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#include "CDC7600.h"

CDC7600::CDC7600 (std::ostream *out, std::list<uint64_t> *program) {
    m_instrMem = new std::list<Instruction>;

    std::list<uint64_t>::const_iterator iterator;
    for (iterator = program->begin(); iterator != program->end(); ++iterator)
        m_instrMem->push_front(Instruction(*iterator));

    m_out = out;
    m_clock = 0;
    m_issue = 1;
    m_issueWord = 1;  // The time the first instruction of this word was issued
}

CDC7600::CDC7600 (std::ostream *out, const Instruction program[],
        const int instrCount) {
    m_instrMem = new std::list<Instruction>;

    for (int i = 0; i < instrCount; ++i)
        m_instrMem->push_front(program[i]);

    m_out = out;
    m_clock = 0;
    m_issue = 1;
    m_issueWord = 1;  // The time the first instruction of this word was issued
}

CDC7600::~CDC7600 () {
    delete m_instrMem;
    m_instrMem = 0;
}

int CDC7600::run () {
    Instruction *instr;

    std::list<Instruction>::const_iterator iterator;
    for (iterator = m_instrMem->begin(); iterator != m_instrMem->end();
            ++iterator) {
        instr = (Instruction *) &iterator;

        // U1 to U2: Translate Instruction and get functional unit

        // Run one instruction
        runInstruction(instr);

        // Calculate issue for next instruction
        if (new instruction same word)
            issue += (instr_Type == “Long”) ? 2 : 1;
        else if (new instruction new word)
            issue = mem_access_time + pc_inc_time;
        issue_word = issue;
    }

    return 0;
}

int CDC7600::runLoop (const int n) {
    int sum = 0;

    // Preparation for looping!
    // Two main things must be done:
    //   1) Fetch the loop counter
    //   2) Fetch the starting address of each vector (Y, A, and B)
    Instruction initFetches(FETCH, 0, 0, 0); // Simulate a fetch
    for (uint8_t i = 0; i < 4; ++i)
        // All four fetches would be independent, so we'll just simulate
        // executing the same instruction four times
        runInstruction(&initFetches);

    // Loop over the function N times
    for (short i = 0; i < n; ++i)
        sum += this->run();

    return sum;
}

void CDC7600::initOutput () {
    (*m_out) << "poop" << std::endl;
}

FunctionalUnit* CDC7600::getFunctionalUnit (Instruction *instr) const {
    // TODO: Yeaaa... should probably figure this one out at some point
    return NULL;
}

std::list<Register> CDC7600::getRegisterOperands (Instruction *instr) const {
    std::list<Register> retVal;

    if ((unsigned int) NULL_OPERAND != instr->getOp1())
        retVal.push_front(instr->getOp1());

    return retVal;
}

void CDC7600::runInstruction (Instruction *instr) {
    unsigned int start, result, fetch, store;
    // Determine this instruction's functional unit and which operands it
    // needs
    FunctionalUnit *funcUnit = getFunctionalUnit(instr);
    std::list<Register> usedOperands = getRegisterOperands(instr);

    // Calculate start based on:
    //     max(issue, functional unit ready, operands ready)
    start = std::max(std::max(m_issue, funcUnit->getUnitReady()),
            getResultsAvailable(&usedOperands));

    // Calculate result
    result = funcUnit->run(start);  // start + execution time

    // Calculate fetch
    switch (instr->getOpcode()) {
        case FETCH:
            fetch = result + CDC7600_MEM_ACCESS_TIME;
            break;
        case STORE:
            store = result + CDC7600_MEM_ACCESS_TIME;
            break;
        default:
            store = fetch = (unsigned int) NULL_OPERAND;
    }
}

unsigned int CDC7600::getResultsAvailable (std::list<Register> *registers) {
    unsigned int ready;
    unsigned int retVal = m_clock;

    std::list<Register>::const_iterator iterator;
    for (iterator = registers->begin(); iterator != registers->end();
            ++iterator) {
        ready = (Register) *iterator;

        if (retVal < ready)
            retVal = ready;
    }

    return retVal;
}
