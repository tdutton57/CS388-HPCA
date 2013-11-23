/**
 * @file    CDC7600.h
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#ifndef CDC7600_H_
#define CDC7600_H_

#include <iostream>
#include <list>
#include "../Instruction.h"

enum state_t {};

class CDC7600 {
    public:
        CDC7600 ();
        virtual ~CDC7600 ();



    protected:
        std::list<Instruction> m_instrMem;
};

#endif /* CDC7600_H_ */
