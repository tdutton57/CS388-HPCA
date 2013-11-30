/**
 * @file    CDC7600.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#include "CDC7600.h"

CDC7600::CDC7600 (std::ostream *out, Instruction program[],
        const unsigned int instrCount) {

    m_out = out;
    m_firstRun = true;
    m_pc = 0;
    m_clock = 0;
    m_issue = 1;
    m_issueWord = 1;  // The time the first instruction of this word was issued

    // Initialize the functional units
    FunctionalUnit::type unit = static_cast<FunctionalUnit::type>(0);
    while (unit < FunctionalUnit::FUNCTIONAL_UNITS) {
        m_funcUnits.push_back(FunctionalUnit(unit));
        unit = static_cast<FunctionalUnit::type>(((int) unit) + 1);
    }

    // Initialize all registers to NULL_OPERAND (signaling that their values are
    // uninitialized which is useful during error-checking)
    Register **banks = new Register*[3];
    banks[0] = m_Rx;
    banks[1] = m_Ra;
    banks[2] = m_Rb;
    for (uint8_t bank = 0; bank < 3; ++bank)
        for (uint8_t reg = 0; reg < CDC7600_REGISTER_BANK_SIZE; ++reg)
            banks[bank][reg] = (Register) NULL_OPERAND;
    delete[] banks;

    // Initialize program memory
    m_instrMem.load(program, instrCount);
}

CDC7600::~CDC7600 () {
    m_out = NULL;
}

int CDC7600::run () {
    Instruction *instr;

    if (m_firstRun) {
        initOutput();
        m_firstRun = !m_firstRun;
    }

    for (unsigned int i = 0; i < m_instrMem.size(); ++i) {
        m_issue += m_instrMem.readInstr(m_pc, instr);

        // Run one instruction
        runInstruction(instr);
        ++m_pc;
    }

    return 0;
}

int CDC7600::runLoop (const int n) {
    int sum = 0;

    // Preparation for looping!
    // Two main things must be done:
    //   1) Fetch the loop counter
    //   2) Fetch the starting address of each vector (Y and X)
    //   3) Fetch all constants (A, B, C)
    Instruction initFetches("", Instruction::INC, Instruction::x0,
            Instruction::x0, Instruction::x0);  // Simulate a fetch
    for (uint8_t i = 0; i < 6; ++i)
        // All four fetches would be independent, so we'll just simulate
        // executing the same instruction four times
        runInstruction(&initFetches);

    // Loop over the function N times
    for (short i = 0; i < n; ++i)
        sum += this->run();

    return sum;
}

void CDC7600::initOutput () {
    *m_out << "Word #" << CDC7600_OUTPUT_DELIM;
    *m_out << "Description" << CDC7600_OUTPUT_DELIM;
    *m_out << "Instr. Type" << CDC7600_OUTPUT_DELIM;
    *m_out << "Issue" << CDC7600_OUTPUT_DELIM;
    *m_out << "Start" << CDC7600_OUTPUT_DELIM;
    *m_out << "Result" << CDC7600_OUTPUT_DELIM;
    *m_out << "Unit Ready" << CDC7600_OUTPUT_DELIM;
    *m_out << "Fetch" << CDC7600_OUTPUT_DELIM;
    *m_out << "Store" << CDC7600_OUTPUT_DELIM << std::endl;
}

// Get the functional unit for an instruction
FunctionalUnit* CDC7600::getFunctionalUnit (const Instruction *instr) {
    FunctionalUnit *requestedUnit;

    switch (instr->getOpcode()) {
        case Instruction::INC:
            requestedUnit = &(m_funcUnits[FunctionalUnit::FU_INC]);  // INC
            break;
        case Instruction::MULF:
            requestedUnit = &(m_funcUnits[FunctionalUnit::FU_MULF]);  // FLOAT_MUL
            break;
        case Instruction::ADDF:
            return &(m_funcUnits[FunctionalUnit::FU_ADDF]);
            break;
        default:
            requestedUnit = NULL;
    }

    return requestedUnit;
}

std::list<Register> CDC7600::getRegisterOperands (Instruction *instr) const {
    std::list<Register> retVal;

    if ((unsigned int) NULL_OPERAND != instr->getOp1())
        retVal.push_front(instr->getOp1());

    return retVal;
}

void CDC7600::runInstruction (Instruction *instr) {
    unsigned int start, result, fetch, store;
    std::stringstream fetchStr, storeStr;

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
    if (Instruction::INC == instr->getOpcode()
            && Instruction::a0 != instr->getOp1())
        switch (instr->getOp1()) {
            case Instruction::a1:
            case Instruction::a2:
            case Instruction::a3:
            case Instruction::a4:
            case Instruction::a5:
                fetch = result + CDC7600_MEM_ACCESS_TIME;
                fetchStr << fetch;
                break;
            case Instruction::a6:
            case Instruction::a7:
                store = result + CDC7600_MEM_ACCESS_TIME;
                storeStr << store;
                break;
        }

    // Output some cool information about this instruction!
    *m_out << instr->getWordNum() << CDC7600_OUTPUT_DELIM;
    *m_out << instr->getDescription() << CDC7600_OUTPUT_DELIM;
    if (Instruction::LONG == instr->getType())
        *m_out << "Long" << CDC7600_OUTPUT_DELIM;
    else
        *m_out << "Short" << CDC7600_OUTPUT_DELIM;
    *m_out << m_issue << CDC7600_OUTPUT_DELIM;
    *m_out << start << CDC7600_OUTPUT_DELIM;
    *m_out << result << CDC7600_OUTPUT_DELIM;
    *m_out << funcUnit->getUnitReady() << CDC7600_OUTPUT_DELIM;
    *m_out << fetchStr.str() << CDC7600_OUTPUT_DELIM;
    *m_out << storeStr.str() << CDC7600_OUTPUT_DELIM;
    *m_out << std::endl;
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
