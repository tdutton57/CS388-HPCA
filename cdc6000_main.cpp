/**
 * @file    cdc6000.cpp
 * @project CS388-HPCA
 *
 * @author  David Zemon, Katie Isbell, Tiffani Dutton
 * @email   david@stlswedespeed.com
 */

#include "cdc6000_main.h"

int main (int argc, char *argv[]) {
    CDC6000 *superPuter;
    std::ofstream *outFile;
    try {
#ifndef RUN_FULL
        Instruction* customProgram;
        std::string userInput;
        unsigned int selection;
        std::ostream *output;

        // Print a greeting
        std::cout
                << "This program will simulate either the CDC6600 or CDC7600 and produce the time "
                << std::endl << "table for a given set of instructions."
                << std::endl << std::endl;

        // Determine which processor to simulate
        std::cout << "Select the processor to simulate from the list below."
                << std::endl;
        std::cout << "\t1. CDC6600" << std::endl;
        std::cout << "\t2. CDC7600" << std::endl;
        std::cout << ">>> ";
        std::getline(std::cin, userInput);
        if (1 == std::atoi(userInput.c_str()))
            superPuter = new CDC6600();
        else if (2 == std::atoi(userInput.c_str()))
            superPuter = new CDC7600();
        else
            throw INVALID_INPUT;

        // Prompt the user to select which program to run
        std::cout << "Select the input to this program from the list below."
                << std::endl;
        std::cout << "\t1. Y = A*X^2 + B" << std::endl;
        std::cout << "\t2. Y = A*X^2 + B*X + c" << std::endl;
        std::cout << "\t3. Y = A*X^2 + B*X + c (X and Y are vectors)"
                << std::endl;
        std::cout << "\t4. Custom program (requires file input)" << std::endl;

        std::cout << ">>> ";
        std::getline(std::cin, userInput);
        selection = std::atoi(userInput.c_str());

        std::cout
                << "Specify the path to which the output will be written. [DEFAULT: stdout]"
                << std::endl;
        std::cout << ">>> ";
        std::getline(std::cin, userInput);

        if (!(userInput.empty())) {
            outFile = new std::ofstream(userInput.c_str());
            if (!(outFile->is_open())) {
                throw FILE_DOES_NOT_EXIST;
            }
            output = outFile;
        } else
            output = &(std::cout);

        // Run the selected program
        switch (selection) {
            case 1:
                superPuter->init(output, program1,
                        sizeof(program1) / sizeof(*program1));
                superPuter->run();
                break;
            case 2:
                superPuter->init(output, program2,
                        sizeof(program2) / sizeof(*program2));
                superPuter->run();
                break;
            case 3:
                std::cout << "How long are the vectors X and Y?" << std::endl
                        << ">>> ";
                std::getline(std::cin, userInput);

                superPuter->init(output, program3,
                        sizeof(program3) / sizeof(*program3));
                superPuter->run(std::atoi(userInput.c_str()));
                break;
            case 4:
                unsigned int instructions;

                std::cout << "Specify the path for your program" << std::endl
                        << ">>> ";
                std::getline(std::cin, userInput);
                instructions = readFile(userInput, customProgram);

                superPuter->init(output, customProgram, instructions);
                superPuter->run();
                break;
            default:
                throw INVALID_INPUT;
        }

        if (outFile->is_open())
            outFile->close();
        delete outFile;
        delete superPuter;
#else
        /**
         * CDC7600 Runs
         */
        // Program 1
        outFile = new std::ofstream("CDC7600_program1.csv");
        superPuter = new CDC7600();
        superPuter->init(outFile, program1,
                sizeof(program1) / sizeof(*program1));
        superPuter->run();
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 2
        outFile = new std::ofstream("CDC7600_program2.csv");
        superPuter = new CDC7600();
        superPuter->init(outFile, program2,
                sizeof(program2) / sizeof(*program2));
        superPuter->run();
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 3.1
        outFile = new std::ofstream("CDC7600_program3_len1.csv");
        superPuter = new CDC7600();
        superPuter->init(outFile, program3,
                sizeof(program3) / sizeof(*program3));
        superPuter->run(1);
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 3.2
        outFile = new std::ofstream("CDC7600_program3_len3.csv");
        superPuter = new CDC7600();
        superPuter->init(outFile, program3,
                sizeof(program3) / sizeof(*program3));
        superPuter->run(3);
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 3.3
        outFile = new std::ofstream("CDC7600_program3_len5.csv");
        superPuter = new CDC7600();
        superPuter->init(outFile, program3,
                sizeof(program3) / sizeof(*program3));
        superPuter->run(5);
        delete superPuter;
        outFile->close();
        delete outFile;

        /**
         * CDC660 Runs
         */
        // Program 1
        outFile = new std::ofstream("CDC6600_program1.csv");
        superPuter = new CDC6600();
        superPuter->init(outFile, program1,
                sizeof(program1) / sizeof(*program1));
        superPuter->run();
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 2
        outFile = new std::ofstream("CDC6600_program2.csv");
        superPuter = new CDC6600();
        superPuter->init(outFile, program2,
                sizeof(program2) / sizeof(*program2));
        superPuter->run();
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 3.1
        outFile = new std::ofstream("CDC6600_program3_len1.csv");
        superPuter = new CDC6600();
        superPuter->init(outFile, program3,
                sizeof(program3) / sizeof(*program3));
        superPuter->run(1);
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 3.2
        outFile = new std::ofstream("CDC6600_program3_len3.csv");
        superPuter = new CDC6600();
        superPuter->init(outFile, program3,
                sizeof(program3) / sizeof(*program3));
        superPuter->run(3);
        delete superPuter;
        outFile->close();
        delete outFile;

        // Program 3.3
        outFile = new std::ofstream("CDC6600_program3_len5.csv");
        superPuter = new CDC6600();
        superPuter->init(outFile, program3,
                sizeof(program3) / sizeof(*program3));
        superPuter->run(5);
        delete superPuter;
        outFile->close();
        delete outFile;
#endif

    } catch (cdc7600_exception &e) {
        std::fprintf(stderr, EXCEPTION_STRINGS[e].c_str());
    }
    return 0;
}

unsigned int readFile (const std::string filename, Instruction* &program) {
    std::ifstream f;
    std::vector<std::string> lines;

    // Open the file for reading...
    f.open(filename.c_str(), std::ios::in);

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

    // Check for empty last line
    if (lines[lines.size() - 1].empty())
        lines.pop_back();

    // Loop through every line of the program and decode the mess
    program = new Instruction[lines.size()];
    for (unsigned int i = 0; i < lines.size(); ++i) {
        std::stringstream parser(lines[i]);
        program[i] = parseLine(parser);
    }

    return lines.size();
}

Instruction parseLine (std::stringstream &ss) {
    std::string instrParts[5];
    for (uint8_t i = 0; i < 5; ++i)
        std::getline(ss, instrParts[i], ',');

    std::string descr = instrParts[0];
    Instruction::opcode_t opcode = Instruction::parseOpcode(instrParts[1]);
    Instruction::register_t op1 = Instruction::parseReg(instrParts[2]);
    Instruction::FlexableOp op2 = Instruction::parseFlexOps(instrParts[3]);
    Instruction::FlexableOp op3 = Instruction::parseFlexOps(instrParts[4]);

    return Instruction(descr, opcode, op1, op2, op3);
}
