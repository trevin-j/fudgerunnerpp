# FudgeRunner++

A Brainfudge interpreter written in C++. This is a port of [FudgeRunner](https://github.com/trevin-j/FudgeRunner), a Brainfudge interpreter written in Java.

# Features

Currently, FudgeRunner++ supports the following features:

* **Interpret file**: Read in a Brainfudge program and execute it.
* **REPL**: Just like any other REPL, you can enter in Brainfudge code and it will be executed.
* **Compile file to executable**: Compile a Brainfudge program to a standalone console application.

Several additional features are currently in development, or planned:

* **Extended file support**: Support for brainfudge programs to read/write files instead of display and user input.

* **Extended memory support**: Support for brainfudge programs to begin running with a preset cell array state. Also, support for seeing the current cell array state.

* **Extended debugging capabilities**: Support for debugging using the interpreter.

# Installation

Currently, there are no releases, so you will need to manually compile FR++. To do so, use CMake to generate build files. Compile the project with your desired compiler. This project is untested on Linux and Mac, but should work anyways. The program should work well on Windows.

NOTE: If you are planning on compiling for Linux or Mac, you will need to change the platform definition in CMakeLists.txt, or some functions of the program will not work as intended. However, most of the program will still work fine, even if you skip this step. This program is completely untested on Mac and Linux, so it may not work at all. Feel free to create an issue or pull request if you find any issues. I'll look them over.

Once compiled, you can run it in the command line using arguments. On windows, if you don't add the executable to the path, you will need to run it via `./fr++` in the same directory as the executable.

The FR++ compiler requires GCC to be installed on your system in order to compile, and the path to the GCC compiler should be added to your PATH environment variable.

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

## Using the Compiler

The compiler can be used to compile a Brainfudge program to a binary executable. The compiler will compile the program to a C file, then compile the C file to a binary executable using gcc. The executable can be run like any other executable, and does not rely on FR++.

To use the compiler, you must specify the file to compile with the `-c` option. You must also specify the output directory with `-o`. Inside the output directory, the FR++ compiler will compile your specified BF program to a C file, then use gcc to compile the C file to an executable. The executable will be placed in the output directory as well. Optionally, you can use the `-k` option to include all your BF comments in the C file. This may be useful for debugging, but isn't at all neccessary. Note that when using the `-k` option, initial comment loops may appear strangely in the C file, but the program will still run as normal.

### Example usage:

To compile a file called `test.bf` to the directory `test_out/`, use the following command:

```
fr++ -c test.bf -o test_out/
```

This will create the directory `test_out/` if it doesn't already exist. The compiler will compile the file `test.bf` to a C file, store that C file as `test.c` then compile the C file to an executable, `test.exe` (on Windows). Both of these files will be placed in the `test_out/` directory. The executable does not rely on the C file, so the C file may be deleted.

To compile a file called `test.bf` to the directory `test_out/`, and include all comments in the C file, use the following command:

```
fr++ -c test.bf -o test_out/ -k
```

Notice that the `-k` option is used. This will include all comments in the C file, which may be useful for debugging. However, it is suggested to debug using the FR++ interpreter instead of the compiler. This will yield more descriptive runtime errors should they occur.
