/* File:    cdc7600.cpp
 * Project: CS388-HPCA
 *
 * Author:  David Zemon
 * Email:   david@stlswedespeed.com
 */

#include "cdc7600.h"

int main (int argc, char *argv[]) {
    std::ifstream f;

    if (0 < argc) {
        f.open(argv[0]);

        if (!(f.is_open()))
            throw "Poooop!";
    } else {
        // TODO: Use default values
    }



    return 0;
}

uint64_t* readFile (std::ifstream &f) {
    uint64_t *instructions;

    return instructions;
}
