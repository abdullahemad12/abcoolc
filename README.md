<h1><img src ="docs/cranberries_white_small.png" alt = "cranberries" width="12%">ABCOOLC</h1>

Abcoolc is a compiler for the COOL programming language. Abcoolc compiles the source program
from the [COOL programming language](https://en.wikipedia.org/wiki/Cool_(programming_language)) to the target assembly code. The assembly code can be executed by [SPIM](https://en.wikipedia.org/wiki/Spim) afterwards.

## Language Overview 

Cool is a small language that can be implemented with reasonable eﬀort. Still, Cool retains many of the features of modern programming languages including objects, static typing, and automatic memory management.

Cool programs are sets of classes. A class encapsulates the variables and procedures of a data type.
Instances of a class are objects. In Cool, classes and types are identiﬁed; i.e., every class deﬁnes a type.
Classes permit programmers to deﬁne new types and associated procedures (or methods) speciﬁc to those
types. Inheritance allows new types to extend the behavior of existing types.

Cool is an expression language. Most Cool constructs are expressions, and every expression has a
value and a type. Cool is type safe: procedures are guaranteed to be applied to data of the correct type.
While static typing imposes a strong discipline on programming in Cool, it guarantees that no runtime
type errors can arise in the execution of Cool programs.
 
For more information refer to the [COOL manual](docs/cool-manual.pdf)

General information on the runtime system and the general code structure refer to [COOL Tour](docs/cool-tour.pdf)

Example programs can be found in the [Examples folder](examples)


## Building the compiler

To be filled in 

## Using the compiler

To be filled in 

## Source code Tour 

Find documentation for each component at the following locations

1. [Lexer](src/lexer)
2. [parser](scr/parser)
