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
        typedef enum _fu_7600_t {
            FU_76_ADDL,
            FU_76_ADDF,
            FU_76_MULF,
            FU_76_DIVF,
            FU_76_NORM,
            FU_76_INC,
            FU_76_POP_COUNT,
            FU_76_BOOL,
            FU_76_SHIFT,
            FUNCTIONAL_UNITS_7600
        } typeCDC7600;

        typedef enum _fu_6600_t {
            FU_66_ADDL,
            FU_66_ADDF,
            FU_66_MULF,
            FU_66_DIVF,
            FU_66_INC,
            FU_66_BOOL,
            FU_66_JMP,
            FU_66_SHIFT,
            FUNCTIONAL_UNITS_6600
        } typeCDC6600;



    public:
        /**
         * @brief   Default Constructor for the FunctionalUnit
         *
         * @param   type Clock cycle that the stage should begin execution
         */
        FunctionalUnit (const typeCDC7600 type);
        FunctionalUnit (const typeCDC6600 type);

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

