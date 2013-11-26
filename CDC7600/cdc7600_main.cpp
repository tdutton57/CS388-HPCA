/**
 * @file    cdc7600.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon
 * @email   david@stlswedespeed.com
 */

#include "cdc7600_main.h"

int main (int argc, char *argv[]) {
    std::list<uint64_t> program;
    CDC7600 *superPuter;

    // Read in the program instructions
//    program = readFile(argc, argv);
//    superPuter = new CDC7600(&program);

    superPuter = new CDC7600(program1, sizeof(program1)/sizeof(*program1));
    superPuter->run();

    return 0;
}

std::list<uint64_t> readFile (int argc, char *argv[]) {
    std::ifstream f;
    std::list<uint64_t> program;
    uint32_t fileLen;
    std::string filename;

    // Open either the file passed in as the argument, or a hard-coded test file
    if (0 == argc) {
        filename = "test.bin";
        // TODO: Present menu to user to select test file
    } else {
        filename = std::string(argv[0]);
    }

    // Open the file for reading...
    f.open(filename.c_str(), std::ios::in | std::ios::binary);
    if (!(f.is_open()))
        throw "Error: File '" + filename + "' cannot be opened";

    // Determine file length
    f.seekg(0, std::ios::end);
    fileLen = f.tellg();
    f.seekg(0, std::ios::beg);

    // Ensure the file is valid - some multiple of 64-bits (one CDC6000 word)
    if (fileLen % WORD_LENGTH)
        throw "Invalid binary file!";

    for (uint32_t i; i < fileLen; i += WORD_LENGTH) {
        uint64_t temp;
        f.read((char *) &temp, sizeof(temp));  // Hack some crap! Read 8 bytes into temp!
        program.push_front(temp);
    }

    return program;
}
