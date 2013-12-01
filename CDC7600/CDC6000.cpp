/**
 * @file    CDC6000.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#include "CDC6000.h"

CDC6000::CDC6000 (std::ostream *out, Instruction program[],
        const unsigned int instrCount) {
    reset();

    m_out = out;

    // Initialize the functional units
    FunctionalUnit::type unit = static_cast<FunctionalUnit::type>(0);
    while (unit < FunctionalUnit::FUNCTIONAL_UNITS) {
        m_funcUnits.push_back(FunctionalUnit(unit));
        unit = static_cast<FunctionalUnit::type>(((int) unit) + 1);
    }

    // Initialize program memory
    m_instrMem.load(program, instrCount);
}

CDC6000::~CDC6000 () {
    reset();
    m_out = NULL;
}

void CDC6000::run () {
    Instruction *instr;

    if (m_firstRun) {
        initOutput();
        m_firstRun = !m_firstRun;
    }

    while (m_pc < m_instrMem.size()) {
        m_issue += m_instrMem.readInstr(m_pc, instr);
        m_issue = std::max(m_issue, getFunctionalUnit(instr)->getUnitReady());

        if (m_instrMem.isNewWord()) {
            if ((unsigned int) NULL_OPERAND != m_wordStart)
                m_issue = std::max(m_issue, m_wordStart + 6); // Yea.. that's right, it's hardcoded. Deal with it
            m_wordStart = m_issue;
        }

        // Run one instruction
        runInstruction(instr);
        ++m_pc;
    }
}

void CDC6000::run (const unsigned int n) {
    if (m_firstRun) {
        initOutput();
        m_firstRun = !m_firstRun;
    }

    // Loop over the function N times
    for (unsigned short i = 0; i < n; ++i) {
        this->run();
        m_pc = 10;
    }
}

void CDC6000::reset () {
    m_firstRun = true;
    m_pc = 0;
    m_clock = 0;
    m_issue = 0;
    m_wordStart = NULL_OPERAND;

    // Reset functional units
    for (unsigned int i = 0; i < m_funcUnits.size(); ++i)
        m_funcUnits[i].reset();

    // Initialize all registers to 0
    CDC6000::Register **banks = new CDC6000::Register*[3];
    banks[0] = m_Rx;
    banks[1] = m_Ra;
    banks[2] = m_Rb;
    for (uint8_t bank = 0; bank < 3; ++bank)
        for (uint8_t reg = 0; reg < CDC7600_REGISTER_BANK_SIZE; ++reg)
            banks[bank][reg].reset();
    delete[] banks;

    m_instrMem.reset();
}

void CDC6000::initOutput () {
    *m_out << "Word #" << CDC7600_OUTPUT_DELIM;
    *m_out << "Instruction" << CDC7600_OUTPUT_DELIM;
    *m_out << "Symantics" << CDC7600_OUTPUT_DELIM;
    *m_out << "Len." << CDC7600_OUTPUT_DELIM;
    *m_out << "Opcode" << CDC7600_OUTPUT_DELIM;
    *m_out << "Issue" << CDC7600_OUTPUT_DELIM;
    *m_out << "Start" << CDC7600_OUTPUT_DELIM;
    *m_out << "Result" << CDC7600_OUTPUT_DELIM;
    *m_out << "Unit Ready" << CDC7600_OUTPUT_DELIM;
    *m_out << "Fetch" << CDC7600_OUTPUT_DELIM;
    *m_out << "Store" << CDC7600_OUTPUT_DELIM << std::endl;
}

void CDC6000::runInstruction (Instruction *instr) {
    unsigned int start = 0, result = 0, fetch = 0, store = 0;
    std::stringstream fetchStr, storeStr;

    // Determine this instruction's functional unit and which operands it
    // needs
    FunctionalUnit *funcUnit = getFunctionalUnit(instr);
    std::list<Instruction::register_t> usedOperands = getDependencyRegisters(
            instr);

    // Calculate start based on:
    //     max(issue, operands ready)
    start = std::max(m_issue, latestDependencyTime(usedOperands));

    // Lock read operands until start
    std::list<Instruction::register_t>::iterator iterator;
    for (iterator = usedOperands.begin(); iterator != usedOperands.end();
            ++iterator)
        getRegisterP(*iterator)->setLock(start);

    // Check for Write-After-Read hazards by determining when the output
    // register is available for writing again
    unsigned int registerUnlock = getRegister(instr->getOp1()).getLock();

    // Calculate result and run the functional unit to calculate unit ready
    result = funcUnit->run(start, registerUnlock);

    // Calculate fetch or store
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
                getRegisterP(
                        static_cast<Instruction::register_t>(instr->getOp1()
                                - Instruction::a0))->setReadReady(fetch);
                break;
            case Instruction::a6:
            case Instruction::a7:
                store = result + CDC7600_MEM_ACCESS_TIME;
                storeStr << store;
                break;
            default:
                break;  // Do nothing special for a0
        }

    getRegisterP(instr->getOp1())->setReadReady(result);

    // Prints the row of information for this instruction into the
    // time table
    printInstrInfo(instr, funcUnit, start, result, fetchStr.str(),
            storeStr.str());
}

void CDC6000::printInstrInfo (const Instruction *instr,
        const FunctionalUnit *funcUnit, const unsigned int start,
        const unsigned int result, const std::string fetchStr,
        const std::string storeStr) {
    char octopusesssss[10];

    // Output some cool information about this instruction!
    *m_out << instr->getWordNum() << CDC7600_OUTPUT_DELIM;
    *m_out << instr->getInstrStr() << CDC7600_OUTPUT_DELIM;
    *m_out << instr->getDescription() << CDC7600_OUTPUT_DELIM;
    if (Instruction::LONG == instr->getType())
        *m_out << "L" << CDC7600_OUTPUT_DELIM;
    else
        /* Implied: if (Instruction::SHORT == instr->getType()) */
        *m_out << "S" << CDC7600_OUTPUT_DELIM;
    sprintf(octopusesssss, "%o", instr->getOpcode());
    *m_out << octopusesssss << CDC7600_OUTPUT_DELIM;
    *m_out << m_issue << CDC7600_OUTPUT_DELIM;
    *m_out << start << CDC7600_OUTPUT_DELIM;
    *m_out << result << CDC7600_OUTPUT_DELIM;
    *m_out << funcUnit->getUnitReady() << CDC7600_OUTPUT_DELIM;
    *m_out << fetchStr << CDC7600_OUTPUT_DELIM;
    *m_out << storeStr << CDC7600_OUTPUT_DELIM;
    *m_out << std::endl;
}

std::list<Instruction::register_t> CDC6000::getDependencyRegisters (
        const Instruction *instr) const {
    std::list<Instruction::register_t> retVal;

    if (instr->getOpType(2))
        retVal.push_back(
                *static_cast<const Instruction::register_t *>(instr->getOp2()));
    if (instr->getOpType(3))
        retVal.push_back(
                *static_cast<const Instruction::register_t *>(instr->getOp3()));

    // If it's a store instruction, add the dependency from the Xn register bank
    if (Instruction::INC == instr->getOpcode()
            && (Instruction::a6 == instr->getOp1()
                    || Instruction::a7 == instr->getOp1())) {
        Instruction::register_t temp = instr->getOp1();
        temp = static_cast<Instruction::register_t>(temp - Instruction::a0);
        retVal.push_back(temp);
    }

    return retVal;
}

const CDC6000::Register CDC6000::getRegister (
        const Instruction::register_t reg) const {
    CDC6000::Register result;

    switch (reg) {
        case Instruction::x0:
        case Instruction::x1:
        case Instruction::x2:
        case Instruction::x3:
        case Instruction::x4:
        case Instruction::x5:
        case Instruction::x6:
        case Instruction::x7:
            result = m_Rx[reg - Instruction::x0];
            break;
        case Instruction::a0:
        case Instruction::a1:
        case Instruction::a2:
        case Instruction::a3:
        case Instruction::a4:
        case Instruction::a5:
        case Instruction::a6:
        case Instruction::a7:
            result = m_Ra[reg - Instruction::a0];
            break;
        case Instruction::b0:
        case Instruction::b1:
        case Instruction::b2:
        case Instruction::b3:
        case Instruction::b4:
        case Instruction::b5:
        case Instruction::b6:
        case Instruction::b7:
            result = m_Rb[reg - Instruction::b0];
    }

    return result;
}

CDC6000::Register* CDC6000::getRegisterP (const Instruction::register_t reg) {
    CDC6000::Register *result;

    switch (reg) {
        case Instruction::x0:
        case Instruction::x1:
        case Instruction::x2:
        case Instruction::x3:
        case Instruction::x4:
        case Instruction::x5:
        case Instruction::x6:
        case Instruction::x7:
            result = &(m_Rx[reg - Instruction::x0]);
            break;
        case Instruction::a0:
        case Instruction::a1:
        case Instruction::a2:
        case Instruction::a3:
        case Instruction::a4:
        case Instruction::a5:
        case Instruction::a6:
        case Instruction::a7:
            result = &(m_Ra[reg - Instruction::a0]);
            break;
        case Instruction::b0:
        case Instruction::b1:
        case Instruction::b2:
        case Instruction::b3:
        case Instruction::b4:
        case Instruction::b5:
        case Instruction::b6:
        case Instruction::b7:
            result = &(m_Rb[reg - Instruction::b0]);
    }

    return result;
}

unsigned int CDC6000::latestDependencyTime (
        const std::list<Instruction::register_t> &registers) {
    unsigned int retVal = m_clock;

    std::list<Instruction::register_t>::const_iterator iterator;
    for (iterator = registers.begin(); iterator != registers.end();
            ++iterator) {
        if (retVal < getRegister(*iterator).getReadReady())
            retVal = getRegister(*iterator).getReadReady();
    }

    return retVal;
}

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
            requestedUnit = &(m_funcUnits[FunctionalUnit::FU_ADDF]);
            break;
        case Instruction::BNQ:
            requestedUnit = &(m_funcUnits[FunctionalUnit::FU_BOOL]);
            break;
        default:
            throw FUNCTIONAL_UNIT_NONEXISTANT;
    }

    return requestedUnit;
}