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
#include "Instruction.h"

class CDC7600 {
    public:
        CDC7600 (std::list<uint64_t> *program);

        CDC7600 (const Instruction program[], const int instrCount);

        ~CDC7600 ();

        int run ();

        int runLoop (const int n);

        void reset ();

    protected:
        std::list<Instruction> *m_instrMem;
};

#endif /* CDC7600_H_ */
