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

FunctionalUnit::FunctionalUnit (const FunctionalUnit::type type) {

    // Set the execution time and segment time of the functional unit
    switch (type) {
        case FU_MULF:
            m_execTime = 5;
            m_segTime = 2;
            break;
        case FU_DIVF:
            m_execTime = 20;
            m_segTime = 18;
            break;
        case FU_NORM:
            m_execTime = 3;
            m_segTime = 3;
            break;
        default:
            // Case for FIXED_ADD, FLOAT_ADD, INC, POP_COUNT, BOOL, and SHIFT types
            m_execTime = 2;
            m_segTime = 1;
    }

    // Initially this functional unit is ready at time 0
    m_ready = 0;
}

unsigned int FunctionalUnit::run (const unsigned int startTime) {
    // Throw an error if the functional unit is busy
    if (m_ready > startTime)
        throw FUNCTIONAL_UNIT_NOT_READY;

    // Update the time for when the functional unit
    // is ready to be used again
    m_ready = startTime + m_segTime;

    // Return the time for when the result has been produced
    // and is ready to be used
    return startTime + m_execTime;
}

