#include <stack>
#include <iostream>
#include <sstream>
#include <fstream>

#include "utils.hpp"
#include "definitions.hpp"

#include "bfcompiler.hpp"

using brainfudge::BFCompiler;


int BFCompiler::bracketsMatch()
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

std::string BFCompiler::indentation(int indentationLevel)
{
    std::stringstream ss;
    ss << "\n";
    for (int i = 0; i < indentationLevel; i++)
    {
        ss << "    ";
    }
    return ss.str();
}

int BFCompiler::compileToC(bool keepComments)
{
    // Check for errors.
    int errorCode = bracketsMatch();
    if (errorCode != BF_OK)
    {
        return errorCode;
    }

    // String stream for the C code.
    std::stringstream ss;

        // Add generated file heading.
    ss  << "// ** Generated C code from Brainfudge. **\n"
        << "// ** Generated by FudgeRunner++ version " << FRPP_VERSION << ". **\n"
        << "// ** This is temporary intermediate code that was generated in the process **\n"
        << "// ** of compiling Brainfudge code. **\n\n"

        // Add includes.
        << "// Include necessary library headers.\n"
        << "#include <stdio.h>\n"
        << "#include <conio.h>\n"

        // Initialize cell array.
        << '\n'
        << "// Initialize cell array.\n"
        << "char array[30000] = {0};\n"
        << "char* ptr = array;\n\n"

        // Add main function.
        << "int main()\n"
        << "{\n";

    // For each instruction, convert to C equivalent and add to string stream
    int indentationLevel = 1;
    bool isComment = false;
    for (int i = 0; i < code.size(); i++)
    {
        // Convert instruction to C equivalent.
        if (code[i] == '>')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "++ptr;";
            continue;
        }
        else if (code[i] == '<')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "--ptr;";
            continue;
        }
        else if (code[i] == '+')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "++*ptr;";
            continue;
        }
        else if (code[i] == '-')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "--*ptr;";
            continue;
        }
        else if (code[i] == '.')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "putchar(*ptr);";
            continue;
        }
        else if (code[i] == ',')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "*ptr = getch();";
            // Force program to break if user uses ctrl+c
            ss << "\n" << indentation(indentationLevel) << "if (*ptr == 3) { return 0; }";
            continue;
        }
        else if (code[i] == '[')
        {
            isComment = false;
            ss << indentation(indentationLevel);
            ss << "while (*ptr)";
            ss << indentation(indentationLevel);
            ss << "{";
            indentationLevel++;
            continue;
        }
        else if (code[i] == ']')
        {
            isComment = false;
            indentationLevel--;
            ss << indentation(indentationLevel);
            ss << "}";
            continue;
        }
        // If the instruction is anything else, it is a comment.
        else if (keepComments)
        {
            if (!isComment)
            {
                ss << "    // ";
                isComment = true;
            }

            // If comment is newline, ignore it.
            if (code[i] == '\n')
            {
                continue;
            }
            ss << code[i];
        }
    }

    // Add generated file footer.
    ss << "\n}";

    // Set the C code.
    cCode = ss.str();

    // Return success.
    return BF_OK;
}

int BFCompiler::saveCompiledC()
{
    // Take cCode and save it all to a new file called "compiled.c" in the buildDir.
    std::ofstream file;
    file.open(buildDir + projectName + ".c");
    file << cCode;
    file.close();

    // Return success.
    return BF_OK;
}

int BFCompiler::compileC()
{
    // Get path to c code.
    std::string cCodePath = buildDir + projectName + ".c";

    // Get output path. On Windows, this is the exe.
    #ifdef WINDOWS
    std::string outputPath = buildDir + projectName + ".exe";
    #else
    std::string outputPath = buildDir + projectName;
    #endif

    std::string command = "gcc " + cCodePath + " -o " + outputPath;

    // Compile the C code.
    system(command.c_str());

    return BF_OK;
}

int BFCompiler::compile(bool keepComments)
{
    // Compile the code to C.
    int errorCode = compileToC(keepComments);
    if (errorCode != BF_OK)
    {
        return errorCode;
    }

    // Save the C code to a file.
    errorCode = saveCompiledC();
    if (errorCode != BF_OK)
    {
        return errorCode;
    }

    // Compile the C code to an executable.
    errorCode = compileC();
    if (errorCode != BF_OK)
    {
        return errorCode;
    }

    // Return success.
    return BF_OK;
}


int BFCompiler::init(const std::string& sourceFile, const std::string& buildDir)
{
    // Set the source file.
    this->sourceFile = sourceFile;

    // Set the build directory.
    // If buildDir doesn't end with a slash, add one.
    if (buildDir.back() != '/')
    {
        this->buildDir = buildDir + "/";
    }
    else
    {
        this->buildDir = buildDir;
    }

    // Verify that the build directory exists.
    // If it doesn't, create it.
    if (!pathExists(buildDir))
    {
        std::cout << "Creating build directory: " << buildDir << std::endl;
        mkdir(buildDir.c_str());
    }

    // Take all the code from the source file and store it in code.
    // If the file cannot be opened, then return an error code ERR_FILE_NOT_FOUND.
    std::ifstream file(sourceFile);
    if (!file.is_open())
    {
        std::cout << std::endl << "Error: Could not open file " << sourceFile << std::endl;
        return ERR_FILE_NOT_FOUND;
    }
    std::stringstream ss;
    ss << file.rdbuf();
    code = strToVector(ss.str());
    file.close();

    // Get the project name from the source file name.
    // Remove the anything after the period, and everything before the last slash
    std::string fileName = sourceFile;
    std::string::size_type lastSlash = fileName.find_last_of("/");
    std::string::size_type lastPeriod = fileName.find_last_of(".");
    projectName = fileName.substr(lastSlash + 1, lastPeriod - lastSlash - 1);

    // Return success.
    return BF_OK;
}


#ifdef WINDOWS
void BFCompiler::runCompiled()
{
    // Get the path to the compiled executable.
    std::string outputPath = buildDir + projectName + ".exe";

    // Command
    std::string command = "start " + outputPath;

    std::cout << "Running compiled executable: " << outputPath << std::endl;

    // Run the compiled executable.
    system(command.c_str());
}
#endif