# FudgeRunner++

A Brainfudge interpreter written in C++. This is a port of [FudgeRunner](https://github.com/trevin-j/FudgeRunner), a Brainfudge interpreter written in Java.

# Features

FR++ currently supports Brainfudge interpretation. All 8 standard Brainfudge commands are supported. 

FR++ also supports a fully-functional REPL for Brainfudge with support for brainfudge instructions on the command-line. Extra commands are also supported such as `clear` to clear the screen, `help` to display a help message, `exit` to exit the REPL, `reset` to reset the interpreter, and `show` to show the current state of the interpreter. **NOTE**: the `clear` command only works if the proper platform is defined in the `CMakeLists.txt` file during compilation.

Several additional features are currently in development, or planned:

* **Compiler**: A Brainfudge compiler which compiles to C, then compiles to a binary executable using a C compiler.

* **Extended file support**: Support for brainfudge programs to read/write files instead of display and user input.

* **Extended memory support**: Support for brainfudge programs to begin running with a preset cell array state. Also, support for seeing the current cell array state.

# Installation

Currently, there are no releases, so you will need to manually compile FR++. To do so, use CMake to generate build files. Compile the project with your desired compiler. This project is untested on Linux and Mac, but should work anyways. The program should work well on Windows.

NOTE: If you are planning on compiling for Linux or Mac, you will need to change the platform definition in main.cpp, or some functions of the program will not work as intended. However, most of the program will still work fine, even if you skip this step.

Once compiled, you can run it in the command line using arguments. On windows, if you don't add the executable to the path, you will need to run it via `./fr++` in the same directory as the executable.

# Usage

## Running a file in the interpreter

Use `fr++ -f <file>` to interpret a file. The file should be a Brainfudge program. The interpreter will run the program and exit. The program runs in a terminal, and supports user interaction.

## Using the REPL

Use `fr++ -r` or `fr++ --repl` to start the REPL. Using no options will also start the REPL. The REPL will run in a terminal, and supports user interaction. The REPL supports all BF instructions, as well as some extra commands, such as `clear`, `help`, `exit`, `reset`, and `show`. Note that each line must be able to be executed on its own in order for the REPL to allow it. For example, if there is an open bracket on the line, it must also contain a close bracket.

### Extra command usage:

* `clear`: clears the terminal screen.
* `help`: displays a Brainfudge cheat sheet.
* `exit`: exits the REPL.
* `reset`: resets the interpreter state.
* `show`: shows the current state of the interpreter.