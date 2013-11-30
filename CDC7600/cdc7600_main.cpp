/**
 * @file    cdc7600.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell
 * @email   david@stlswedespeed.com
 */

#include "cdc7600_main.h"

int main (int argc, char *argv[]) {
    CDC7600 *superPuter;

#ifndef DEBUG
    std::ofstream OUT_FILE(OUT_FILENAME);
    if (!(OUT_FILE.is_open())) {
        throw FILE_DOES_NOT_EXIST;
    }
#endif

    // Read in the program instructions
    //Instruction *program;
    //program = readFile(argc, argv);
    //superPuter = new CDC7600(&program);

    // Print a greeting
    std::cout
            << "This program will simulate the CDC7600 and produce the time table for a"
            << std::endl << "given set of instructions." << std::endl
            << std::endl;

    // Prompt the user to select the program to run
    std::cout << "Select the input to this program from the list below."
            << std::endl;

    std::cout << "\t1. Y = A*X^2 + B" << std::endl;
    std::cout << "\t2. Y = A*X^2 + B*X + c" << std::endl;
    std::cout << "\t3. Y = A*X^2 + B*X + c (X and Y are vectors)" << std::endl;
    std::cout << ">>> ";

    unsigned int selectedProgram;
    std::cin >> selectedProgram;

    // Run the selected program
    try {
        switch (selectedProgram) {
            case 1:
                superPuter = new CDC7600(&OUTPUT, program1,
                        sizeof(program1) / sizeof(*program1));
                superPuter->run();
                break;
            case 2:
                superPuter = new CDC7600(&OUTPUT, program2,
                        sizeof(program2) / sizeof(*program2));
                superPuter->run();
                break;
            case 3:
                unsigned int n;
                std::cout << "How long are the vectors X and Y?" << std::endl
                        << ">>> ";
                std::cin >> n;
                throw NOT_IMPLEMENTED_YET;
                superPuter->runLoop(n);
                break;
            default:
                throw INVALID_INPUT;
        }
    } catch (cdc7600_exception &e) {
        std::fprintf(stderr, CDC7600_EXCEPTION_STRINGS[e].c_str());
    }

#ifndef DEBUG
    OUT_FILE.close();
#endif

    return 0;
}

Instruction* readFile (int argc, char *argv[]) {
    Instruction *program;
    std::ifstream f;
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
        throw FILE_DOES_NOT_EXIST;
    }

// Read in all lines of the program
    std::string line;
    do {
        std::getline(f, line);
        lines.push_back(line);
    } while (!(f.eof()));

// Loop through every line of the program and decode the mess
    program = new Instruction[lines.size()];
    for (unsigned int i = 0; i < lines.size(); ++i) {
        // TODO: Write huge lookup tables that do this correctly
//        program[i] = Instruction();
    }

    return program;
}
