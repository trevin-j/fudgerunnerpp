#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <stack>
#include <string>


namespace brainfudge
{
    class Interpreter
    {
    private:
        // Pointer to current cell.
        int cellPtr;

        // Pointer to current instruction.
        int codePtr;

        // Vector of instructions.
        std::vector<char> code;

        // Vector of cells.
        std::vector<char> cells;

        // Stack for looping instructions.
        // Each element is the pointer to the open loop.
        std::stack<int> loopStack;

        int largestInstructionYet;

        // Determine if all the brackets in the instrucctions are matched.
        // 0 means no error.
        // 1 means extra open bracket.
        // 2 means extra close bracket.
        int bracketsMatch();

        // Process the current instruction. Does not increment codePtr.
        // Returns 0 if successful, and error code otherwise.
        int processInstruction();

    public:
        // Constructor.
        Interpreter();

        // Set the instructions for the interpreter.
        void setInstructions(const std::string& instructions);

        // Run the BF code, using the console for IO.
        // Return 0 if the code runs successfully.
        // Otherwise, return an error code.
        int runBF();

        // Add new instructions to the end of the code.
        void addInstructions(const std::string& instructions);

        // Reset the interpreter.
        void reset();

        // Print out some data about the interpreter to the screen.
        void show();
    };
}

#endif