# Syntax Analysis and Parse Tree Generator for SQL like language
The repository contains two programs:
* A lex and yacc based code for syntax analysis of an SQL like language.
* A C++ based implementation of syntax analysis and parse tree generator for an SQL like language.


### Yacc based implementation
The yacc contains the grammar for an sql query language. The grammar is similar to predicate logic progamming. It is a simple way of creating your own languages, and follows a backtracking based automated system to check syntax validity of the SQL query.

The lex file parses the query and separates it into keywords that are passed into yacc file containing the grammar.

### C++ code for parse tree generation
A backtracking based code performs the similar task of syntax analysis as Yacc. We try to replicate the internal backtracking algorithm. The code takes as input the query, and checks for syntax errors. It prints the Parse tree for each query if it is entered correctly.

The parse tree generation is crucial for any compiler and helps in visualizing how recursion unfolds in complex situations.