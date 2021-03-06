<h1><span><img src ="docs/art/abcoolc-logo.png" alt = "cranberries" width="12%"></span></h1>

ABCOOLC is my implementation of a compiler for the [COOL programming language](https://en.wikipedia.org/wiki/Cool_(programming_language)). ABCOOLC compiles the source program from COOL to MIPS assembly code, which can be executed afterwards by [SPIM](https://en.wikipedia.org/wiki/Spim).

# Language Overview 

Cool is a small language that can be implemented with reasonable eﬀort. Still, Cool retains many of the features of modern programming languages including objects, static typing, and automatic memory management.

Cool programs are sets of classes. A class encapsulates the variables and procedures of a data type.
Instances of a class are objects. In Cool, classes and types are identiﬁed; i.e., every class deﬁnes a type.

Classes permit programmers to deﬁne new types and associated procedures (or methods) speciﬁc to those
types. Inheritance allows new types to extend the behavior of existing types.

Cool is an expression language. Most Cool constructs are expressions, and every expression has a
value and a type. Cool is type safe: procedures are guaranteed to be applied to data of the correct type.
While static typing imposes a strong discipline on programming in Cool, it guarantees that no runtime
type errors can arise in the execution of Cool programs.
 
For more information about COOL refer to the [COOL manual](docs/cool-manual.pdf)

For general information about the runtime system and the code structure refer to [COOL Tour](docs/cool-tour.pdf)

example COOL programs can be found in the [Examples folder](examples)


# Building for Linux (from source)

Abcoolc is designed to run on linux machines.

## Dependencies 

- build-essential (for debian distros)
- base-devel (for archlinux)
- gcc/g++ (11 or higher)
- SPIM (mips simulator)

## Installing the compiler

**Note:** if you get something like `bash: ./script: Permission denied` error, then make the 'build', 'install' and 'uninstall' files exectuble. For example, run `chmod a+x install`.

- To build abcoolc run:

`./build`

- To install abcoolc run:

`./install`

This will install abcoolc and clspim (a version of spim configured to load the COOL run-time system before running the compiled code). 

You can test that abcoolc and clspim were installed successfully by running

`abcoolc -v`
> ABCOOLC version d.d.d

`clspim -v`
> CLSPIM version d.d.d

**Note** that even though this installs a compiled version of SPIM, it does not necessarily install all
the dependencies required to run SPIM. Therefore it is necessary to install SPIM seperately from the official source.

- To uninstall the abcoolc run:

`./uninstall`

this will remove all the abcoolc binaries and files installed (if any) including clspim.

## Using the compiler

By convention COOL programs have the extension ".cl". To compile a COOL program consisting of the files
file_1.cl, file_2.cl, file_3.cl ...... file_n.cl, run the following command: 

`abcoolc file_1.cl file_2.cl file_3.cl [-o outputfile.s]`

note that -o is an optional parameter. If it is not supplied, the output file will have the name "file_1.s". 

## Running the code

CLSPIM is used to run the code generated by abcoolc as follows:

`clspim outputfile.s`

# Source code Tour 

Like many [compilers](https://en.wikipedia.org/wiki/Compiler), abcoolc has four phases before the final code is generated.

1. Lexical Analysis: individual words and names are identified as tokens.
2. Parsing: the structure of tokens is recognized as a program and the abstract syntax tree is constructed.
3. Semantics Analysis: program validitions and type checking are done in this phase according to the COOL type checking and semantics rules.
4. Code Generation: the abstract syntax tree is translated to MIPS assembly program according to the operational semantics of COOL.

Each of this component is seperated as its own program and later glued together by pipes to form the complete abcoolc compiler. 

Find documentation for each component at the following locations

1. [Lexer](src/lexer)
2. [parser](src/parser)
3. [Analyzer](src/analyzer)
4. [Cgen](src/cgen)


#### Disclaimer

Some parts of the code found here is attributed to Prof. Alex Aiken and StanfordOnline - SOE.YCSCS1. My own contribution counts as ~11500 lines of code and the documentation of the four components.