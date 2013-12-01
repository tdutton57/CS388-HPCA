/**
 * @file    FunctionalUnit.h
 * @project CDC7600
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 *
 * @description
 */

#ifndef FUNCTIONALUNIT_H_
#define FUNCTIONALUNIT_H_

#include <stdint.h>
#include "CDC7600_Exceptions.h"

/**
 * @brief   This class represents one of several functional units used by the
 *          CDC7600
 */
class FunctionalUnit {
    public:
        // These are the functional unit types for the
        // CDC7600
        typedef enum _fu_t {
            FU_ADDL,
            FU_ADDF,
            FU_MULF,
            FU_DIVF,
            FU_NORM,
            FU_INC,
            FU_POP_COUNT,
            FU_BOOL,
            FU_SHIFT,
            FUNCTIONAL_UNITS
        } type;

    public:
        /**
         * @brief   Default Constructor for the FunctionalUnit
         *
         * @param   type Clock cycle that the stage should begin execution
         */
        FunctionalUnit (const type type);

        void reset ();

        /**
         * @brief   Run the functional unit and return the time for when the
         *          result is ready
         *
         * @param   startTime   Clock cycle time for when the functional unit
         *                      begins execution
         *
         * @return  Clock cycle when the result is ready after using the
         *          functional unit
         */
        unsigned int run (const unsigned int startTime,
                const unsigned int outputRegUnlocked);

        /**
         * @brief   Function that returns the time for when the functional
         *          unit is ready
         *
         * @return  The time in clock cycles when the functional unit is ready
         */
        unsigned int getUnitReady () const {
            return m_ready;
        }

    protected:
        unsigned int m_ready;  // The time (in clock cycles) when the functional unit is ready
        uint8_t m_execTime;  // The execution time of the functional unit
        uint8_t m_segTime;  // The segment time of the functional unit
};

#endif /* FUNCTIONALUNIT_H_ */

