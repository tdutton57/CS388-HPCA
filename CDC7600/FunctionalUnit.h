/**
 * @file    FunctionalUnit.h
 * @project CDC7600
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#ifndef FUNCTIONALUNIT_H_
#define FUNCTIONALUNIT_H_

#include <stdint.h>

typedef enum _fu_t {
    FIXED_ADD,
    FLOAT_ADD,
    FLOAT_MUL,
    FLOAT_DIV,
    NORMALIZE,
    INC,
    POP_COUNT,
    BOOL,
    SHIFT,
    FU_TYPES
} fu_t;

/**
 *
 */
class FunctionalUnit {
    public:
        FunctionalUnit (const fu_t type);

        /**
         * @brief   Run the functional unit
         *
         * @param   Clock cycle that the functional unit should begin execution
         *
         * @return  Clock cycle when result is has been written
         */
        unsigned int run (const unsigned int startTime);

        /**
         *
         */
        unsigned int getUnitReady();

    protected:
        uint8_t m_execTime;
        uint8_t m_segTime;
        unsigned int m_ready;
};

#endif /* FUNCTIONALUNIT_H_ */
