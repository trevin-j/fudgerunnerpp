#include <iostream>

#include <conio.h>

#include "interpreter.hpp"
#include "utils.hpp"

#include "definitions.hpp"

using brainfudge::Interpreter;


int Interpreter::bracketsMatch()
{
    // Use a stack to keep track of open bracket location.
    std::stack<int> openBracketStack;

    // Loop through the instructions.
    for (int i = 0; i < code.size(); i++)
    {
        // If the instruction is an open bracket, push the location onto the stack.
        if (code[i] == '[')
        {
            openBracketStack.push(i);
        }
        // If the instruction is a close bracket, pop the location off the stack.
        else if (code[i] == ']')
        {
            // If the stack is empty, then there is a close bracket without an open bracket.
            if (openBracketStack.empty())
            {
                std::cout << std::endl << "Error: Unmatched close bracket at instruction " << i << std::endl;
                return ERR_EXTRA_CLOSE_BRACKET;
            }
            // Otherwise, pop the location off the stack.
            else
            {
                openBracketStack.pop();
            }
        }
    }

    // If the stack is not empty, then there is an open bracket without a close bracket.
    if (!openBracketStack.empty())
    {
        std::cout << std::endl << "Error: Unmatched open bracket at instruction " << openBracketStack.top() << std::endl;
        return ERR_EXTRA_OPEN_BRACKET;
    }

    // If we get here, then all the brackets are matched.
    return BF_OK;
}


Interpreter::Interpreter()
{
    reset();
}


void Interpreter::setInstructions(const std::string& instructions)
{
    code = strToVector(instructions);
}


void Interpreter::addInstructions(const std::string& instructions)
{
    // Get new instructions as vector.
    std::vector<char> newCode = strToVector(instructions);

    // Reserve the space for the new instructions to prevent extra reallocation.
    code.reserve(code.size() + newCode.size());

    // Add the new instructions to the end of the code.
    for (int i = 0; i < newCode.size(); i++)
    {
        code.push_back(newCode[i]);
    }
}


int Interpreter::runBF()
{
    // Run pre-check to make sure the brackets are matched.
    int status = bracketsMatch();
    if (!status == BF_OK)
    {
        reset();
        return status;
    }

    // While there are instructions left to process, process them.
    // Ignore characters that are not instructions.
    while (codePtr < code.size())
    {
        // Process the next instruction.
        int result = processInstruction();
        if (result != BF_OK)
        {
            reset();
            return result;
        }
        codePtr++;
    }

    // If we get here, then the code ran successfully.
    return BF_OK;
}


void Interpreter::reset()
{
    // Clear the member variables.
    cellPtr = 0;
    codePtr = 0;
    code.clear();
    cells.clear();
    cells.push_back(0);
    while (!loopStack.empty())
    {
        loopStack.pop();
    }
    largestInstructionYet = 0;
}


int Interpreter::processInstruction()
{
    if (PRINT_TRACE && codePtr > largestInstructionYet)
    {
        largestInstructionYet = codePtr;
        std::cout << code[codePtr];
    }

    char instruction = code[codePtr];
    std::string allowedInstructions = "><+-.,[]";

    // If the instruction is not a valid instruction, ignore it and return.
    if (allowedInstructions.find(instruction) == std::string::npos)
    {
        return BF_OK;
    }

    // Ensure enough cells exist
    while (cells.size() <= cellPtr)
    {
        cells.push_back(0);
    }

    // Process the instruction.

    // Increment/decrement cell value.
    if (instruction == '+')
    {
        cells[cellPtr]++;
        return BF_OK;
    }
    if (instruction == '-')
    {
        cells[cellPtr]--;
        return BF_OK;
    }

    // Increment/decrement cell pointer.
    if (instruction == '>')
    {
        cellPtr++;
        return BF_OK;
    }
    if (instruction == '<')
    {
        cellPtr--;

        // If cellPtr is negative, then there is an error.
        if (cellPtr < 0)
        {
            std::cout << std::endl << "Error: Cell pointer out of bounds at instruction " << int(codePtr) << std::endl;
            return ERR_CELL_PTR_OUT_OF_BOUNDS;
        }

        return BF_OK;
    }

    // Input/output.
    if (instruction == '.')
    {
        std::cout << cells[cellPtr];
        return BF_OK;
    }
    if (instruction == ',')
    {
        cells[cellPtr] = getch();
        if (cells[cellPtr] == 3)
        {
            return ERR_EARLY_TERMINATION;
        } 
        return BF_OK;
    }


    // Looping
    if (instruction == '[')
    {
        if (cells[cellPtr] != 0)
        {
            loopStack.push(codePtr);
        }
        else
        {
            // Skip to matching close bracket.
            int bracketCount = 0;
            while (true)
            {
                codePtr++;
                if (code[codePtr] == '[')
                {
                    bracketCount++;
                    continue;
                }
                if (code[codePtr] == ']')
                {
                    if (bracketCount == 0)
                    {
                        break;
                    }
                    bracketCount--;
                }
            }
        }
        return BF_OK;
    }

    if (instruction == ']')
    {
        // Move pointer back to the matching open bracket.
        codePtr = loopStack.top() - 1;
        loopStack.pop();
        return BF_OK;
    }

    // If we get here, something unexpected happened.
    std::cout << std::endl << "Error: Unexpected result at instruction " << int(codePtr) << std::endl;
    return ERR_UNEXPECTED_RESULT;
}


void Interpreter::show()
{
    std::cout << "Cell #: " << cellPtr << "; Cell value: " << int(cells[cellPtr]) << ';' << std::endl;
}
