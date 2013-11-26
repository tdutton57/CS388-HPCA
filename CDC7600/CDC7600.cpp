/**
 * @file    CDC7600.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#include "CDC7600.h"

CDC7600::CDC7600 (std::list<uint64_t> *program) {
    m_instrMem = new std::list<Instruction>;

    std::list<uint64_t>::const_iterator iterator;
    for (iterator = program->begin(); iterator != program->end(); ++iterator)
        m_instrMem->push_front(Instruction(*iterator));
}

CDC7600::CDC7600 (const Instruction program[], const int instrCount) {
    m_instrMem = new std::list<Instruction>;

    for (int i = 0; i < instrCount; ++i)
        m_instrMem->push_front(program[i]);
}

CDC7600::~CDC7600() {
    delete m_instrMem;
    m_instrMem = 0;
}

int CDC7600::run () {

    return 0;
}

int CDC7600::runLoop (const int n) {
    int sum = 0;

    // TODO: Perform first fetch (fetch N)

    // Loop over the function N times
    for (short i = 0; i < n; ++i)
        sum += this->run();

    return sum;
}
