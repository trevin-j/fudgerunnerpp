#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>

#include "interpreter.hpp"
#include "utils.hpp"
#include "arg_parser.hpp"

// Define version.
#define FRPP_VERSION "0.1.0"

int main(int argc, char** argv)
{
    ArgParser parser(argc, argv);

    // If flag -h is passed, print help and exit.
    if (parser.cmdOptionExists("-h") || parser.cmdOptionExists("--help"))
    {
        std::cout
            << "FudgeRunner++ - Brainfudge Interpreter, REPL, and Compiler" << std::endl
            << std::endl
            << "Usage:" << std::endl
            << "  fr++ [options]" << std::endl
            << std::endl
            << "Options:" << std::endl
            << "  -h, --help       Display help menu." << std::endl
            << "  -f <file>        Specify a file to interpret." << std::endl
            // << "  -r, --repl       Run the REPL. If no options" << std::endl
            // << "                   are passed, the REPL will run." << std::endl
            // << "  -c <file> <out>  Compile a file to a binary" << std::endl
            // << "                   file. The output file will be" << std::endl
            // << "                   <out>." << std::endl
            << "  -v, --version    Display version information." << std::endl
            << std::endl;

        return 0;
    }


    // If flag -v is passed, print version and exit.
    if (parser.cmdOptionExists("-v") || parser.cmdOptionExists("--version"))
    {
        std::cout << "FudgeRunner++ version " << FRPP_VERSION << std::endl;
        return 0;
    }


    // If flag -f is passed, interpret the file.
    if (parser.cmdOptionExists("-f"))
    {
        std::string file = parser.getCmdOption("-f");
        std::ifstream ifs(file);

        if (!ifs.is_open())
        {
            std::cout << "Error: Could not open file " << file << std::endl;
            return 1;
        }

        std::stringstream buffer;
        buffer << ifs.rdbuf();

        ifs.close();

        brainfudge::Interpreter interpreter;
        interpreter.setInstructions(buffer.str());

        int result = interpreter.runBF();

        std::cout << std::endl << "Brainfudge program terminated with code " << result << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        getch();

        return 0;
    }





}