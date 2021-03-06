/**
 * @file    FunctionalUnit.cpp
 * @project CDC7600
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#include "FunctionalUnit.h"

FunctionalUnit::FunctionalUnit (const FunctionalUnit::typeCDC7600 type) {

    // Set the execution time and segment time of the functional unit
    //TODO: fix for CDC6600
    switch (type) {
        case FU_76_MULF:
            m_execTime = 5;
            m_segTime = 2;
            break;
        case FU_76_DIVF:
            m_execTime = 20;
            m_segTime = 18;
            break;
        case FU_76_NORM:
            m_execTime = 3;
            m_segTime = 3;
            break;
        case FU_76_ADDF:
            m_execTime = 4;
            m_segTime = 1;
            break;
        default:
            // Case for FIXED_ADD, INC, POP_COUNT, BOOL, and SHIFT types
            m_execTime = 2;
            m_segTime = 1;
    }
    reset();
}

FunctionalUnit::FunctionalUnit (const FunctionalUnit::typeCDC6600 type) {
    //CDC 6600
    switch(type) {
        case FU_66_MULF:
            m_execTime = 10;
            break;
        case FU_66_JMP:
            m_execTime = 8; // Only true for Bi compared with Bj
            break;
        case FU_66_ADDF:
            m_execTime = 4;
            break;
        case FU_66_DIVF:
            m_execTime = 29;
            break;
        default:
            m_execTime = 3;
    }
    m_segTime = m_execTime + 1;
    reset();
}

void FunctionalUnit::reset () {
    // Initially this functional unit is ready at time 0
    m_ready = 0;
}

unsigned int FunctionalUnit::run (const unsigned int startTime,
        const unsigned int outputRegUnlocked) {
    unsigned int resultReady;
    // Throw an error if the functional unit is busy
    if (m_ready > startTime)
        throw FUNCTIONAL_UNIT_NOT_READY;

    // Update the time for when the functional unit
    // is ready to be used again
    m_ready = startTime + m_segTime;

    // Return the time for when the result has been produced
    // and is ready to be used
    resultReady = startTime + m_execTime;

    // Delay the result if requested to
    if (resultReady < outputRegUnlocked) {
        resultReady = outputRegUnlocked;
    }

    // NOTE: Not checking for traffic jams

    return resultReady;
}
