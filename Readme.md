## Brainfuck with few extras
## Written in C++ 
---
# requirements to build
* MinGW Compiler Pack
* GNU Make (with its executable added to PATH)

# build
Open shell in project directory and type:
> make auto

# run
Get the compiled file from the bin subdirectory. Run from the command line with the wanted options. Each option consists of a hyphen, option symbol and a string. It cannot contain whitespaces.
Most minimal call would look like:
> bxx -ffile.bpp

Which orders the interpreter to run file.bpp that is our source file and is located in the same directory as the executable.

By default commands are parsed from left to right.

# list of command line switches
* -f[file]
Specifies which file to parse. Mandatory.
* -v
Generates more inforamtion during interpreter startup.
* -v2
Generates more information during program execution. (temporarily defunct)
* -s
There will be no output form interpreter at all! Mutually exclusive with -v and -v2.
* -b[no_of_blocks]
Specifies number of memory blocks to allocate. If not set will allocate 300.
* -p[pos]
Starting position of the program pointer. Default set to memory block number 0.

# planned
1. Support for all types of [ExtendedBrainfuck](https://esolangs.org/wiki/Extended_Brainfuck)
2. Compiler
3. improved performance & memory usage