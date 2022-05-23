# FudgeRunner++

A Brainfudge interpreter written in C++. This is a port of [FudgeRunner](https://github.com/trevin-j/FudgeRunner), a Brainfudge interpreter written in Java.

# Features

FR++ currently supports Brainfudge interpretation. All 8 standard Brainfudge commands are supported. Several features are currently in development, or planned:

* **REPL**: A fully-functional REPL for Brainfudge with support for brainfudge instructions on the command-line. Extra commands will also be supported such as `clear` to clear the screen, `help` to display a help message, `exit` to exit the REPL, `load` to load a file, `save` to save a file, `reset` to reset the interpreter, and `show` to show the current state of the interpreter.

* **Compiler**: A Brainfudge compiler which compiles to C, then compiles to a binary executable using a C compiler.

* **Extended file support**: Support for brainfudge programs to read/write files instead of display and user input.

# Installation

Currently, there are no releases, so you will need to manually compile FR++. To do so, use CMake to generate build files. Compile the project with your desired compiler. This project is untested on Linux and Mac, but should work anyways. The program should work well on Windows.

Once compiled, you can run it in the command line using arguments. On windows, if you don't add the executable to the path, you will need to run it via `./fr++` in the same directory as the executable.

# Usage

## Running a file in the interpreter

Use `fr++ -f <file>` to interpret a file. The file should be a Brainfudge program. The interpreter will run the program and exit. The program runs in a terminal, and supports user interaction.