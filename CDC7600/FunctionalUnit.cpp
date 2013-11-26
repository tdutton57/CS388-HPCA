/**
 * @file    FunctionalUnit.cpp
 * @project CDC7600
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#include "FunctionalUnit.h"

FunctionalUnit::FunctionalUnit (const fu_t type) {
    switch (type) {
        case FLOAT_MUL:
            m_segTime = 2;
            break;
        case FLOAT_DIV:
            m_segTime = 18;
            break;
        default:
            m_segTime = 1;
    }

    switch (type) {
        case FLOAT_MUL:
            m_execTime = 5;
            break;
        case FLOAT_DIV:
            m_execTime = 20;
            break;
        case NORMALIZE:
            m_execTime = 3;
            break;
        default:
            m_execTime = 2;
    }

    m_ready = 0;
}

unsigned int FunctionalUnit::run (const unsigned int startTime) {
    if (m_ready > startTime)
        throw "Functional unit not ready!";

    m_ready = startTime + m_segTime;

    return startTime + m_execTime;
}

unsigned int FunctionalUnit::getUnitReady () {
    return m_ready;
}
