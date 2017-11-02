/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CREATE = 258,
    TABLE = 259,
    INT = 260,
    CHAR = 261,
    DECIMAL = 262,
    NOT = 263,
    NULLX = 264,
    FROM = 265,
    SELECT = 266,
    INSERT = 267,
    INTO = 268,
    VALUES = 269,
    SET = 270,
    UPDATE = 271,
    DELETE = 272,
    DROP = 273,
    ALTER = 274,
    ADD = 275,
    COLUMN = 276,
    STRING = 277,
    INTVAL = 278,
    ALL = 279,
    DISTINCT = 280,
    WHERE = 281,
    IN = 282,
    REFERENCES = 283,
    PRIMARY = 284,
    FOREIGN = 285,
    DEFAULT = 286,
    UNIQUE = 287,
    KEY = 288,
    ANY = 289,
    VARCHAR = 290,
    EXISTS = 291,
    CHECK = 292,
    LITERAL = 293,
    OR = 294,
    AND = 295,
    COMPARATOR = 296
  };
#endif
/* Tokens.  */
#define CREATE 258
#define TABLE 259
#define INT 260
#define CHAR 261
#define DECIMAL 262
#define NOT 263
#define NULLX 264
#define FROM 265
#define SELECT 266
#define INSERT 267
#define INTO 268
#define VALUES 269
#define SET 270
#define UPDATE 271
#define DELETE 272
#define DROP 273
#define ALTER 274
#define ADD 275
#define COLUMN 276
#define STRING 277
#define INTVAL 278
#define ALL 279
#define DISTINCT 280
#define WHERE 281
#define IN 282
#define REFERENCES 283
#define PRIMARY 284
#define FOREIGN 285
#define DEFAULT 286
#define UNIQUE 287
#define KEY 288
#define ANY 289
#define VARCHAR 290
#define EXISTS 291
#define CHECK 292
#define LITERAL 293
#define OR 294
#define AND 295
#define COMPARATOR 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "yacc.y" /* yacc.c:1909  */
 int id; char str[100];

#line 139 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
