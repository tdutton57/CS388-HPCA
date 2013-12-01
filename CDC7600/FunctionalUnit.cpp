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
    //TODO: fix for CDC6600
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
        case FU_ADDF:
            m_execTime = 4;
            m_segTime = 1;
            break;
        default:
            // Case for FIXED_ADD, INC, POP_COUNT, BOOL, and SHIFT types
            m_execTime = 2;
            m_segTime = 1;
    }

    //CDC 6600
    switch(type) {
        //floating point multiplier (2x)
        case FU_MULF:
            m_execTime = 5;
            m_segTime = 5;
            break;

        //floating point divide
        case FU_DIVF:
            m_execTime = 34;
            m_segTime = 34;
            break;

        //floating point add
        case FU_ADDF:
            m_execTime = 4;
            m_segTime = 4;
            break;

        //"long" integer add
        case FU_LNGADD:
            m_execTime = 2;
            m_segTime = 2;
            break;

        //incrementers (2 copies; performed memory load/store)
        case FU_INC:
            m_execTime = 3;
            m_segTime = 3;
            break;

        //shift boolean and branch integer Add
        case default:
            m_execTime = 3;
            m_segTime = 3;

    }
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
