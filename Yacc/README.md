### Yacc based implementation
The yacc contains the grammar for an sql query language. The grammar is similar to predicate logic progamming. It is a simple way of creating your own languages, and follows a backtracking based automated system to check syntax validity of the SQL query.

The lex file parses the query and separates it into keywords that are passed into yacc file containing the grammar.

To install lex and yacc use:

```
$ sudo apt-get install flex
$ sudo apt-get install bison
```
To execute the program: 

```
$ lex lex.l
$ yacc -d yacc.y
$ gcc -o sql lex.yy.c y.tab.c
```