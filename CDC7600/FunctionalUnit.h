/**
 * @file    Stage.h
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

class FunctionalUnit {
    public:
        FunctionalUnit (const fu_t type);

        /**
         * @brief   Run the the scoreboard stage
         *
         * @param   Clock cycle that the stage should begin execution
         *
         * @return  Clock cycle when stage has completed
         */
        unsigned int run (const unsigned int startTime);

        /**
         *
         */
        unsigned int getUnitReady ();

    protected:
        uint8_t m_execTime;
        unsigned int m_ready;
        uint8_t m_segTime;
};

#endif /* FUNCTIONALUNIT_H_ */
