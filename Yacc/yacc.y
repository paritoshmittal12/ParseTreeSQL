%{
#include <stdio.h>
int yylex(void);
void yyerror (const char *s);
int line_no  = 1;
%}

%define parse.error verbose

%union { int id; char str[100];} 
																								/* types of token */
%start code
%token CREATE TABLE INT CHAR DECIMAL NOT NULLX FROM SELECT INSERT INTO VALUES SET UPDATE DELETE DROP ALTER ADD COLUMN 			/* tokens for sql */
%token STRING INTVAL ALL DISTINCT WHERE IN REFERENCES PRIMARY FOREIGN DEFAULT UNIQUE KEY ANY VARCHAR EXISTS CHECK LITERAL
%type <str> STRING element
%type <id> INTVAL

%left OR 								/*  left associative operators */
%left AND
%left NOT
%left COMPARATOR
%left '+' '-'
%left '*' '/'

%%

code 				: line semi		  		{ line_no++;}
					| code line semi 		{ line_no++;}
					| error semi			{ printf("Error in line number %d.\n",line_no++);yyerrok;}
					| code error semi		{ printf("Error in line number %d.\n",line_no++);yyerrok;}
					;

line 				: create_table 											/* line is the starting terminal */
					| select_statement 
                    | insert_statement 
                    | update_statement 
                    | delete_statement 
                    | drop_table 
                    | alter_table 
                    ;

semi 				: ';'
					;

create_table		: CREATE TABLE element '(' table_element_list ')' 			{ printf("created table %s\n", $3);}	/* create table production */
					;


table_element_list	: table_element 											
					| table_element_list ',' table_element
					;

table_element 		: element element_type element_constraint 			{ printf("table column %s\n", $1);}		/* column names in table or constraint */
					| table_constraint
					;

table_constraint 	: PRIMARY KEY '(' element_list ')'								/* constraints in table */
					| FOREIGN KEY '(' element_list ')' REFERENCES element
					| UNIQUE '(' element_list ')'
					| NOT NULLX
					| CHECK '(' where_to_find ')'
					;

select_statement	: SELECT distinct_or_not elements clause 						/*  select production rule */
					;

distinct_or_not		:
					|ALL
					|DISTINCT
					;

from_select 		: element element
					| element
					| from_select ',' element element
					| from_select ',' element
					;

clause				: FROM from_select
					  if_where_to_find
					;

if_where_to_find	: 
					| WHERE where_to_find
					;

where_to_find 		: where_to_find OR where_to_find 						/* where conditions */
					| where_to_find AND where_to_find
					| NOT where_to_find
					| '(' where_to_find ')'
					| where_condition
					| equality
					;

equality 			: select_unit '=' select_unit
					| select_unit '=' '(' select_statement ')'
					; 

where_condition		: select_unit IN '(' element_list ')'
					| select_unit NOT IN '(' element_list ')' 					
					| select_unit IN '(' select_statement ')'
					| select_unit NOT IN '(' select_statement ')'
					| select_unit COMPARATOR select_unit
					| select_unit COMPARATOR '(' select_statement ')'
					| select_unit COMPARATOR all_any '(' select_statement ')'
					| EXISTS '(' select_statement ')'
					;

all_any				: ALL
					| ANY
					;

select_unit			: select_unit '+' select_unit 								/* simple expressions */
					| select_unit '-' select_unit
					| select_unit '*' select_unit
					| select_unit '/' select_unit
					| element
					| INTVAL
					| '(' select_unit ')'
					| LITERAL
					;

elements 			: '*'
					| element '.' element
					| element
					| elements ',' element '.' element
					| elements ',' element
					;

element_list 		: element
					| element_list ',' element
					;

element_constraint 	: 
					| NOT NULLX
					| PRIMARY KEY
					| UNIQUE
					| DEFAULT NULLX 
					;

element				: STRING 							
					;

element_type		: INT 												/* data types */
					| CHAR '(' INTVAL ')'
					| DECIMAL '(' INTVAL ')'
					| VARCHAR '(' INTVAL ')'
					;

insert_statement    : INSERT INTO table_name VALUES '(' insert_list ')' 		/* insert production rule */
                    | INSERT INTO table_name select_statement
                    ;

insert_list 		: LITERAL
					| 
					| INTVAL
					| insert_list ',' INTVAL
					| insert_list ',' LITERAL

table_name          : element
                    | element '(' element_list ')'
                    ;

update_statement    : UPDATE element SET column_values if_where_to_find  		/* update production rule */
                    ;

column_values       : element '=' select_unit                    
                    | column_values ',' element '=' select_unit
                    ;

delete_statement    : DELETE FROM element if_where_to_find						/* delete production rule */
                    ;

drop_table          : DROP TABLE element 										/* drop table production rule*/
                    ;

alter_table         : ALTER TABLE element ADD element element_type 				/* alter table production rule */
                    | ALTER TABLE element DROP COLUMN element
                    ;

%%

int main(void)
{
	return yyparse();
}

void yyerror(const char *s)
{
	fprintf(stderr,"%s.\n",s);
}

