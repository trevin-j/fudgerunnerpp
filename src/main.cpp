#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>

#include "interpreter.hpp"
#include "utils.hpp"
#include "arg_parser.hpp"

#include "definitions.hpp"
#include "bfcompiler.hpp"


// Display help information to the user
int help()
{
    std::cout
            << "** FudgeRunner++ - Brainfudge Interpreter, REPL, and Compiler **" << std::endl
            << std::endl
            << "Usage:" << std::endl
            << "  fr++ [options]" << std::endl
            << std::endl
            << "Options:" << std::endl
            << "  -h, --help          Display help menu." << std::endl
            << "  -f <file>           Specify a file to interpret." << std::endl
            << "  -r, --repl          Run the REPL. If no options" << std::endl
            << "                      are passed, the REPL will run." << std::endl
            << "  -c <file> -o <out>  Compile a file to a binary" << std::endl
            << "                      file. The output file will be" << std::endl
            << "                      <out>." << std::endl
            << "  -v, --version       Display version information." << std::endl
            << "  -k                  Keep the comments from the BF code" << std::endl
            << "                      in the intermediate C code." << std::endl
            #ifdef WINDOWS
            << "  --run               Run the binary after it has been compiled." << std::endl
            #endif
            << std::endl
            << "For more information, see the README file," << std::endl
            << "or visit the public repo at\n" << PUBLIC_REPO << std::endl
            << std::endl;

        return 0;
}

// Display version information to user
int version()
{
    std::cout
        << "** FudgeRunner++ - Brainfudge Interpreter, REPL, and Compiler **" << std::endl
        << "** Version: " << FRPP_VERSION << " **" << std::endl
        << "\n** View the public repo at " << PUBLIC_REPO << " **" << std::endl;
    
    return 0;
}

// Interpret a file
int interpretFile(const ArgParser& parser)
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

// Print a BF cheatsheet
void helpBF()
{
    std::cout << std::endl
        << "Brainfudge Cheatsheet" << std::endl
        << "=====================" << std::endl
        << ">  Increment the data pointer." << std::endl
        << "<  Decrement the data pointer." << std::endl
        << "+  Increment the data at the data pointer." << std::endl
        << "-  Decrement the data at the data pointer." << std::endl
        << "[  Jump forward if the data at the data pointer is 0." << std::endl
        << "]  Jump backward if the data at the data pointer is not 0." << std::endl
        << ".  Output the data at the data pointer." << std::endl
        << ",  Input a character to the data pointer." << std::endl;
}

// Run the BF REPL
int runREPL()
{
    brainfudge::Interpreter interpreter;
    int commandNumber = 0;

    std::cout << "[REPL]: FudgeRunner++ Brainfudge REPL activated.";

    // Loop until user quits
    while (true)
    {
        std::cout << std::endl << std::endl;
        std::cout << "[" << commandNumber << "]: ";
        commandNumber++;

        std::string input;
        std::getline(std::cin, input);

        // Deal with REPL commands
        if (input == "exit")
        {
            std::cout << "[REPL]: Exiting..." << std::endl;
            return 0;
        }
        if (input == "help")
        {
            helpBF();
            continue;
        }
        if (input == "show")
        {
            interpreter.show();
            continue;
        }
        if (input == "reset")
        {
            interpreter.reset();
            std::cout << "[REPL]: Interpreter reset." << std::endl;
            continue;
        }
        if (input == "clear")
        {
            clear();
            continue;
        }
        // TODO: add more commands including: save, load

        // Interpret the input
        interpreter.addInstructions(input);
        std::cout << "[OUT]> ";
        interpreter.runBF();
    }
}


int compile(const ArgParser& parser)
{
    // Get src file and build directory.
    std::string srcFile = parser.getCmdOption("-c");
    std::string buildDir = parser.getCmdOption("-o");

    // Create compiler object
    brainfudge::BFCompiler compiler;

    // Initialize compiler
    int initStatus = compiler.init(srcFile, buildDir);

    // Check if compiler was initialized successfully
    if (initStatus != BF_OK)
    {
        std::cout << "Error: Could not initialize compiler." << std::endl;
        return 1;
    }

    // Compile the file
    compiler.compile(parser.cmdOptionExists("-k"));

    // If the user wants to run the compiled file, run it
    if (parser.cmdOptionExists("--run"))
    {
        std::cout << "Running compiled file..." << std::endl;
        compiler.runCompiled();
    }

    return BF_OK;
}


int main(int argc, char** argv)
{
    ArgParser parser(argc, argv);

    // If flag -h is passed, print help and exit.
    if (parser.cmdOptionExists("-h") || parser.cmdOptionExists("--help"))
    {
        return help();
    }

    // If flag -v is passed, print version and exit.
    if (parser.cmdOptionExists("-v") || parser.cmdOptionExists("--version"))
    {
        return version();
    }

    // If flag -f is passed, interpret the file.
    if (parser.cmdOptionExists("-f"))
    {
        return interpretFile(parser);
    }

    // If flag -r is passed, run the REPL.
    if (parser.cmdOptionExists("-r") || parser.cmdOptionExists("--repl"))
    {
        return runREPL();
    }

    // If flag -c and -o are passed, compile the file.
    if (parser.cmdOptionExists("-c") && parser.cmdOptionExists("-o"))
    {
        return compile(parser);
    }

    // If no flags are passed, run the REPL.
    if (argc == 1)
    {
        return runREPL();
    }

    // If we get here, the user passed an invalid flag.
    std::cout << "Error: Invalid options." << std::endl;
}