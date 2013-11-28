/**
 * @file    cdc7600.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#include "cdc7600_main.h"

int main (int argc, char *argv[]) {
    Instruction *program;
    CDC7600 *superPuter;

    // Read in the program instructions
    //    program = readFile(argc, argv);
    //    superPuter = new CDC7600(&program);

    // Print a greeting
    std::cout
            << "This program will simulate the CDC7600 and produce the time table "
                    "for a given set of instructions.\n";

    // Prompt the user to select the program to run
    std::cout << "Select the input to this program from the list below.\n"
            << "Enter just the number that corresponds to the equation.\n";

    std::cout << "1. Y = Ax^2 + B\n";
    std::cout << "2. Y = Ax^2 + Bx + c\n";
    std::cout << "3. Y = Ax^2 + Bx + c (X and Y are vectors)\n";

    unsigned int selectedProgram;
    std::cin >> selectedProgram;

    // Run the selected program
    switch (selectedProgram) {
        case 1:
            superPuter = new CDC7600(&std::cout, program1,
                    sizeof(program1) / sizeof(*program1));
            break;
        case 2:
            superPuter = new CDC7600(&std::cout, program2,
                    sizeof(program2) / sizeof(*program2));
            break;
        case 3:
            break;
        default:
            throw "Invalid input!";
    }

    superPuter->run();

    delete[] program;

    return 0;
}

Instruction* readFile (int argc, char *argv[]) {
    Instruction *program;
    std::ifstream f;
    uint32_t fileLen;
    std::string filename;
    std::vector<std::string> lines;

    // Open either the file passed in as the argument, or a hard-coded test file
    if (0 == argc) {
        filename = "test.bin";

    } else {
        filename = std::string(argv[0]);
    }

    // Open the file for reading...
    f.open(filename.c_str(), std::ios::in | std::ios::binary);

    // Throw an error if the given file path does not exist
    if (!(f.is_open())) {
        throw "Error: File '" + filename + "' cannot be opened";
    }

    // Read in all lines of the program

    return program;
}
