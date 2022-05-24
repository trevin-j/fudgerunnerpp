#ifndef BFCOMPILER_HPP
#define BFCOMPILER_HPP

#include <vector>
#include <string>

;

namespace brainfudge
{
    class BFCompiler
    {
    private:
        // Vector of instructions.
        std::vector<char> code;

        // String of the C code.
        std::string cCode;

        // String of the build directory.
        std::string buildDir;

        // String of the source file.
        std::string sourceFile;

        // String of the output file name, derived from the source file name.
        std::string projectName;

        // Determine if all the brackets in the instrucctions are matched.
        // 0 means no error.
        // 1 means extra open bracket.
        // 2 means extra close bracket.
        int bracketsMatch();

        // Compile all the BF code to C
        // Compiles the code saved in code, and saves the C code in cCode.
        // Returns a code indicating the success of the compilation.
        // KeepComments: If true, then comments are kept in the C code.
        int compileToC(bool keepComments);

        // Save all the C code to a file
        // Takes in the C code as a string, and saves it to a temporary file.
        // Returns a code indicating success or failure.
        int saveCompiledC();

        // Compile the saved C code to an executable
        int compileC();

        // Get a string of the indentation.
        std::string indentation(int indentationLevel);

    public:
        // Constructor.
        BFCompiler() = default;

        // Compile the BF code to a console application.
        // Return 0 if the code compiles successfully.
        // Otherwise, return an error code.
        // KeepComments: If true, then comments are kept in the C code.
        int compile(bool keepComments = false);

        // Initialize the BFCompiler. Must be called before compiling.
        // Returns a code indicating success or failure.
        int init(const std::string& sourceFile, const std::string& buildDir);
    };
}


#endif