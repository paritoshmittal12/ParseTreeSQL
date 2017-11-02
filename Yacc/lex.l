%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
int line_number=1;
int query_number=1;
#define KEYS(val,val1){ printf(" => %s is a Keyword.\n",val);return val1; /* keywords are inserted here */}
#define LIT(val,val1){char a[100]; int len = strlen(val); strncpy(a,(val + 1), len-2);a[len -2] = '\0'; printf(" => %s is a LITERAL.\n",a);return val1; /* keywords are inserted here */}
#define ID(val){ printf(" => %s is an Identifier.\n",val);strcpy(yylval.str, yytext); return STRING; /* Identifiers are inserted here */}
#define NUM(val){ printf(" => %s is a Number.\n",val);yylval.id = atoi(yytext); return INTVAL; /* number are inserted here */}
#define OP(val){ printf(" => %c is an Operator.\n",val);return val; }
#define OPE(val){ printf(" => %s is an Operator.\n",val);return COMPARATOR; /* comparators are inserted here */}
#define SC(val){printf(" => %d number query is finished.\n",query_number); query_number++;return val;}

#define errorFunc(val){printf(" => %s pops an Error in %d \n",val,line_number);}


%}

%%

exit  						{printf("GoodBye :) \n");exit (EXIT_SUCCESS); /* exit command */}
(?i:"CREATE")	                KEYS(yytext,CREATE)
(?i:"TABLE")                     KEYS(yytext,TABLE)
(?i:"SELECT")                    KEYS(yytext,SELECT)
(?i:"FROM")                      KEYS(yytext,FROM)
(?i:"INT")                       KEYS(yytext,INT)
(?i:"DECIMAL") 					KEYS(yytext,DECIMAL)
(?i:"VARCHAR") 					KEYS(yytext,VARCHAR)	
(?i:"NOT")                      KEYS(yytext,NOT)
(?i:"NULL")                     KEYS(yytext,NULLX)
(?i:"CHAR")                     KEYS(yytext,CHAR)
(?i:"ALL")						KEYS(yytext,ALL)
(?i:"DISTINCT")					KEYS(yytext,DISTINCT)
(?i:"WHERE")					KEYS(yytext,WHERE)
(?i:"IN")						KEYS(yytext,IN)
(?i:"INSERT")					KEYS(yytext,INSERT)
(?i:"INTO")						KEYS(yytext,INTO)
(?i:"VALUES")					KEYS(yytext,VALUES)
(?i:"SET")						KEYS(yytext,SET)
(?i:"UPDATE")					KEYS(yytext,UPDATE)
(?i:"DELETE")					KEYS(yytext,DELETE)
(?i:"DROP")						KEYS(yytext,DROP)
(?i:"ALTER")					KEYS(yytext,ALTER)
(?i:"ADD")						KEYS(yytext,ADD)
(?i:"COLUMN")					KEYS(yytext,COLUMN)
(?i:"ANY")						KEYS(yytext,ANY)
(?i:"EXISTS")  					KEYS(yytext,EXISTS)
(?i:"PRIMARY") 					KEYS(yytext,PRIMARY)
(?i:"FOREIGN") 					KEYS(yytext,FOREIGN)
(?i:"KEY") 						KEYS(yytext,KEY)
(?i:"UNIQUE") 					KEYS(yytext,UNIQUE)
(?i:"DEFAULT") 					KEYS(yytext,DEFAULT)
(?i:"CHECK") 					KEYS(yytext,CHECK)
(?i:"REFERENCES") 				KEYS(yytext,REFERENCES)
(?i:"AND")	 					KEYS(yytext,AND)
(?i:"OR") 						KEYS(yytext,OR)

"<>"						OPE("<>") 
">="						OPE(">=")
"<="						OPE("<=")
">"							OPE(">")
"<"							OPE("<")
[a-zA-Z][a-zA-Z0-9_]*		ID(yytext)
[0-9]*[a-zA-z]+[a-zA-Z0-9_]*				{errorFunc(yytext); /* error function */}
[0-9]+ 						NUM(yytext)
[0-9]*"."[0-9]+				NUM(yytext)
[()*,+-/=.] 				OP(yytext[0])
[;] 						SC(yytext[0])
L?\"(\\.|[^\\"])*\" 		LIT(yytext,LITERAL)
'[^']*'						LIT(yytext,LITERAL)
[ \t\r]		         		;
[\n]						{line_number++;};
. 						{ errorFunc(yytext);}
%% 

int yywrap(void){return 1;}
