# Introduction
This project is the first step to understand the implementation of programming languages. Based on the book "Crafting Interpreters" - Robert Nystrom, I tried to implement Lox interpreter in C++. 

> ALL CODE IS BASED ON THE BOOK: [link to the book](https://craftinginterpreters.com)
# Stages of interprerter

- Scanner:
    - Transform the stream of chars (source code) into `Token`s. Every token consists of type, name (lexem), a releted literal object and the line where it occured.
- Parser:
    - The role of the parser is to make `AST` out of tokens, which come from the scanner.
- AST Interpreter:
    - It is responsible for executing a banch of ASTs which are intermediate form of the given script in Lox.

The implementaion of Lox features are mainly place in `Parser` and `AST Interpreter` which will be discussed in more detail in the following sections.

## Parser

Parser distinguish:

- Delcaration:
    - Variable declaration
    - Function declaration
    - Statement declaration:
        - For statement
        - If statement
        - Print statement
        - While statement
        - Block statement
        - Expression statement:
            - expression
            - assignment
            - logic_or
            - logic_and
            - equality
            - comparison
            - term
            - factor
            - unary
            - call
            - primary

Declarations are atoms of the parser that separate language features. Statements are everything which don't require storing data and expression are operation on data (a.k.a variables). This division of responsibilities ensures compactness of language.

When it comest to data structures using by parser, the output is a vector of statements (every declaration inherits from `Stmt class`). Each statement class points on functionality of Lox e.g. looping control flow, branching control flow declaring and defining variables etc; and contains data required in that process as expression class.

## AST Interpreter

The interpreter implements two visitors interfaces. One for statements and one for expression. Statement objects use `execute` function to control the program execution flow (i.e. how the program is executing) which happens by consuming successive `Stmt` classes. Wherever the interpreter meets an expression class, it uses `eveluate` function to get data using in the program.

# Program execution flow

Every details about Lox emplementaion will be described here.

## Environments

Environments are implementaion of scoping where each instance point on the nearest external scope. This class is a part of `block` functionality.

## Functions

The Lox interpreter need a new expression and declaration (a class which inferites from `Stmt`) to impelemnt functions. 

The new delcaration is responsible for containing information about function body and parameters. When the visitor function catches this statement, it adds the function name to the environment in order to register a function. Then the interpreter stores an instance of `LoxFunction` class which knows how to 'execute' functions in Lox. 

The expression `Call` is related with using defined functions. If the interpreter finds this expression, it will looks for the object to 'call' in the current environment. Only if it is `LoxFunction` object, the interpreter will execute it as a function.

When it comest to environments, all 'LoxFunction' objects have `closure` field which indicates the environment of origin. If the functions represented by this object is called,  the function environments has `closure` as a parent.