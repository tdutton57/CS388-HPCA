/* CDC7600.h
 * CS388-HPCA
 *
 *  Author: David Zemon
 *   Email: david@stlswedespeed.com
 */

#ifndef CDC7600_H_
#define CDC7600_H_

#include <iostream>
#include "Instruction.h"

enum state_t {};

class CDC7600 {
    public:
        CDC7600 ();
        virtual ~CDC7600 ();



    protected:
        Instruction *m_instrMem;
};

#endif /* CDC7600_H_ */
