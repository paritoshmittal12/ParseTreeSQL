/*
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------WELCOME------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
/*The Code of RD parser of SQL in C++ where code has a functionality to print the Parse tree of input string if accepted*/
/*The necessary libraries*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

/*standard definitions*/
#define bool int
#define true 1
#define false 0

// global variables
/*the position of pointer in tokens array*/
int pos=0;
/*The array of tokens populated by the input string for further analysis*/
char tokens[200][20];
int total=0;
int maxparse=0;


/*A function to Handle wide spaces*/
int stringNotSpace(string s){
	for(int i=0;i<s.size();i++)
		if(s[i]!=' ')
			return 1;
	return 0;
}

/*if the string has a syntax error, then function points to the place where error is detected*/
void syntaxError(char str[]){
	int count=0;
	int cnt_spaces=0;

	//if(maxparse!=total-1)
	{
	int i=0;
	while(str[i]==' ')
		i++;
	for(;str[i]!='\0';i++)
	{
		count++;
		if(str[i]==' ' )
			cnt_spaces++;
		else if(str[i]==',' || str[i]=='.' || str[i]=='>' || str[i]=='<' || str[i]=='=' || str[i]=='(' || str[i]==')')
			cnt_spaces=cnt_spaces+2;
		if(cnt_spaces==maxparse)
			break;
	}

	cout<<endl<<std::string(count,' ')<<"^"<<endl;
	cout<<std::string(count,' ')<<"unexpected input here"<<endl;
}
}
/*A class based implementation of Parse tree. Each terminal or non-terminal of an accepted string is actually the node of the tree and member functions are called whenever a link
from parent to child is being made.*/
class tree{
	int indent;
	int parent_ind;
	string s;
	std::vector<tree> c;
	/*the member functions of class for various features*/
public:
	tree(string s);
	
	void updateparent(int l){
		parent_ind=l;
	}
	void updateIndent(int k){
		indent=k;
	}
	int getVal(){
		if(stringNotSpace(s))
		{	cout<<s;
			return 1;
		}
		return 0;
	}
	int  getindent(){
		if(stringNotSpace(s))
			return indent;
		else 
			return -1;
	}
	int  getparent(){
		if(stringNotSpace(s))
			return parent_ind;
		else 
			return -1;
	}
	string retVal(){
		return s;
	}
	void addChild(tree t);
	
	int getSize(){
		return c.size();
	}
	
	void setVal(string k);
	void showAllStatus(std::vector<tree> &q);
	void addToQ(std::vector<tree> &q);
	void addLeaf(string k);
	tree retChild(int i);
};
tree tree::retChild(int i){
	return this->c[i];
}
/*Tree constructor*/
tree::tree(string k){
	this->s=k;
	this->indent=15;
	this->parent_ind=0;
}
/*If we add a terminal to the graph then it will be a leaf node and hence a seperate function to identify them differently*/
void tree::addLeaf(string k){
	tree p(k);
	this->addChild(p);
}
void tree::setVal(string k){
	this->s=k;
}
/*to add elements to the Graph*/
void tree::addChild(tree t){
	c.push_back(t);
}
/*The function prints a BFS of the parse tree so obtained */
void tree::showAllStatus(std::vector<tree> &q){

	if(!this->c.size()){
		return;
	}
	int k=0;
	int t=q.size();
	int count=60;
	int count1=60;
	while(t){
		int poit=1;
		cout<<std::string(count1,' ');
		count1=count1/2;
		
		int flag=0,flag1=0;
		int p=0;

		int parent_f=0;
		for(int i=k;i<t;i++){
			int indent=q[i].getindent();
			int parent=q[i].getparent();
			if(parent !=-1 && parent_f==0 ){
				p=parent;
				cout<<parent<<":: ";
				parent_f=1;
			}

			if(p!=parent && indent!=-1 && flag1==1){

		 		cout<<std::string(indent,' ');
		 		cout<<parent<<":: ";
		 		p=parent;
		 	}
		 		
			int tm=q[i].getVal();
			
		 	if(tm){
		 		cout<<"->"<<i<<" ";
		 		cout<<std::string(count,' ');
		 		if(flag1==0)
		 			flag1=1;		 		
		 	}
		 	
			for(int j=0;j<(q[i].c).size();j++){
				(q[i].c)[j].updateIndent(indent);
				(q[i].c)[j].updateparent(i);
				q.push_back((q[i].c)[j]);

			}
		}
		cout<<endl;
		flag1=0;
		count=count/2;
		if(t!=q.size()){
			k=t;
			t=q.size();
		}
		else
			t=0;
	}
}
void tree::addToQ(std::vector<tree> &q){
	for(int i=0;i<this->c.size();i++){
		q.push_back(this->c[i]);
	 	
	 }
}
/*The following listed are the non terminals of the grammar, each having its own seperate function for Recurive Descent*/
bool start(tree &t);
bool l_prime(tree &t);
bool create_table(tree &t);
bool table_element_list(tree &t);
bool table_element_list_prime(tree &t);
bool table_element(tree &t);
bool table_constraint(tree &t);
bool select_statement(tree &t);
bool distinct_or_not(tree &t);
bool from_select(tree &t);
bool from_select_prime(tree &t);
bool clause(tree &t);
bool if_where_to_find(tree &t);
bool where_to_find(tree &t);
bool where_to_find_prime(tree &t);
bool in_condition(tree &t);
bool select_unit(tree &t);
bool select_unit_prime(tree &t);
bool elements(tree &t);
bool element_list(tree &t);
bool element_list_prime(tree &t);
bool element_constraint(tree &t);
bool element(tree &t);
bool element_type(tree &t);
bool insert_statement(tree &t);
bool table_name(tree &t);
bool update_statement(tree &t);
bool column_values(tree &t);
bool column_values_prime(tree &t);
bool delete_statement(tree &t);
bool drop_table(tree &t);
bool alter_table(tree &t);
bool T(tree &t);
bool X(tree &t);
bool Y(tree &t);
bool Z(tree &t);
bool F(tree &t);
bool T_prime(tree &t);
bool elements_prime(tree &t);
bool retBool(bool i){
	return i;
}
/*
term function takes a non-terminal(or token) as input and checks of the position pointer (pos) points to the same token from tokens array, if so then position pointer is updated and
parser moves ahead..............
*/
bool term(const char * str){
	int k=strcmp(tokens[pos],str);
	pos++;
	if(k==0)
		return true;
	return false;
}


void clean_buffer(){
	for(int i=0;i<200;i++){
		strcpy(tokens[i],"\0");
	}
	pos=0;
	total=0;
	maxparse=0;
}

/*
-----------------------------------------------------------------------------------LEXICAL ANALYSIS BEGINS------------------------------------------------------------------------------------------------
*/
/*The following functions are required to perform LEXICAL ANALYSYS */
// Identifies and Handles particular tokens in a string to be parsed
int tokenthis(char in[],char token[],int * pos)
{
	int i=*pos,j=0;
	int flag=0;
	while(in[i]!='\0')
	{
		if(in[i]=='('){
			*pos=i+1;token[j]='\0';return 1;
		}
		else if(in[i]==')'){
			*pos=i+1;token[j]='\0';return 2;
		}
		else if(in[i]==','){
			*pos=i+1;token[j]='\0';return 3;
                }
		else if(in[i]=='>' && in[i+1]=='='){
			*pos=i+2;token[j]='\0';return 4;
		    }
		else if(in[i]=='<'&& in[i+1]=='='){
			*pos=i+2;token[j]='\0';return 5;
		    }
		else if(in[i]=='<'&& in[i+1]=='>'){
			*pos=i+2;token[j]='\0';return 6;
		    }
		else if(in[i]=='<'){
			*pos=i+1;token[j]='\0';return 7;
		    }
		else if(in[i]=='>'){
			*pos=i+1;token[j]='\0';return 8;
		    }
		else if(in[i]=='='){
			*pos=i+1;token[j]='\0';return 9;
		    }
		else if(in[i]=='-'){
			*pos=i+1;token[j]='\0';return 10;
		    }
		else if(in[i]=='+'){
			*pos=i+1;token[j]='\0';return 11;
		    }
		else if(in[i]=='*'){
			*pos=i+1;token[j]='\0';return 12;
		    }
		else if(in[i]=='/'){
			*pos=i+1;token[j]='\0';return 13;
                }
		else if(in[i]==' ' && in[i+1]==' ')
			i++;
        else if(in[i]==';'){
			*pos=i+1;token[j]='\0';return 14;
            }
		else if(in[i]==' ' || in[i]=='\n' || in[i]=='\t'){
			*pos=i+1;token[j]='\0';return 15;
		}
		else if(in[i]=='"'){
			*pos=i+1;token[j]='\0';return 16;
		}
		else if(in[i]=='.'){
			*pos=i+1;token[j]='\0';return 17;
		}
		else
			token[j++]=in[i++];
	}	
	*pos=i;
	token[j]='\0';
	return 0;
}




void printsep(int k){
		if(k==1) printf("  => '(' is an Operator.\n");
		else if(k==2) printf("  => ')' is an Operator.\n");
		else if(k==3) printf("  => ',' is an Operator.\n");
		else if(k==4) printf("  => '>=' is an Operator.\n");
		else if(k==5) printf("  => '<=' is an Operator.\n");
		else if(k==6) printf("  => '<>' is an Operator.\n");
		else if(k==7) printf("  => '<' is an Operator.\n");
		else if(k==8) printf("  => '>' is an Operator.\n");
		else if(k==9) printf("  => '=' is an Operator.\n");
		else if(k==10) printf("  => '-' is an Operator.\n");
		else if(k==11) printf("  => '+' is an Operator.\n");
		else if(k==12) printf("  => '*' is an Operator.\n");
		else if(k==13) printf("  => '/' is an Operator.\n");
		else if(k==14) printf("  => ';' read. Query ends here.\n");
}





int  checkID(char token[]){
	
	int i=0,flag=0;     					//flag 1=num, flag 2=invalid, flag 3=identifier, flag 4=decimal
	while(token[i]!='\0' && flag!=2){
		if(isdigit(token[i])){
			if(flag==0)
				flag=1;		
		}
		else if(token[i]!='.'){
			if(flag==1){
				flag=2;
			}
			else if(flag==0){
				
				if(isalpha(token[0]))    flag=3;
				else flag=2;
			}
			else if(flag==4){
				flag=2;
			}		
		}
		else{
			if(flag==0){
				flag=2;
			}
			else if(flag==1){
				flag=4;			
			}
			else if(flag==4){
				flag=2;
			}
		}
		i++;
	}
	return flag;
}


/*This function makes the code case sensitive thereby making it similar to an actual SQL compiler*/
void changecase(char token[],char str[]){
	int i;
	for( i=0;token[i]!='\0';i++)
	{ if(isalpha(token[i]))
		str[i]=toupper(token[i]);
	}
	str[i]='\0';
}

int checksemi(char line[]){
	int len=strlen(line);
	if(line[len-2]==';')
		return 1;
	return 0;
}


void  parseline(char input[]){
int posn=0,loop=1;
char token[50],str[50];
char present[500];
/*The following is the Token class*/
const char *keywords[63] = {"ADD","ALL","AS","ALTER","AND","ANY","ASC","AVG","BY","CHAR","CHARACTER","COLUMN",
"CREATE","CASCADE","CONSTRAINTS","DATE","DISTINCT","DOUBLE","DEFAULT","DELETE","DESC","DROP","EXISTS","FOREIGN",
"FLOAT","FROM","GROUP","HAVING","IN","INDEX","INSERT","INTO","IS","INT","INTEGER","JOIN","KEY","LEFT","LIKE",
"MAX","MIN","NOT","NULL","OR","ORDER","OUTER","REFERENCES","RIGHT","SCHEMA","SELECT","SET","SMALLINT","SUM",
"TABLE","UNION","UNIQUE","UPDATE","VALUE","VALUES","VARCHAR","WHERE","PRIMARY","DECIMAL"};



int flag=0,key=1,ID_check;
clean_buffer();
int Lex_Error=0;

int fl=1;
int fll=checksemi(input);




int strt=0;
while(key=tokenthis(input,token,&posn)){
		fl=1;
		flag=0;
		for(int i=0;i<63;i++){
			changecase(token,str);
			if(strcmp(keywords[i],str)==0){
				strcpy(tokens[pos],keywords[i]);
				pos++;
				flag=1;
				break;	
			}
		}


		if(flag!=1 && strcmp(token,"")!=0){
			ID_check=checkID(token);	
			if(ID_check==1 || ID_check==4)
				strcpy(tokens[pos++],"INTVAL");
			else if(ID_check==3)
				strcpy(tokens[pos++],"STRING");
			else
				Lex_Error=1;
		}

		//store the special characters in the tokens too:
		if(key<=9 && key>=4)
			strcpy(tokens[pos++],"COMPARATOR");
		else if(key==10) strcpy(tokens[pos++],"-");
		else if(key==11) strcpy(tokens[pos++],"+");
		else if(key==12) strcpy(tokens[pos++],"*");
		else if(key==13) strcpy(tokens[pos++],"/");
		else if(key==1) strcpy(tokens[pos++],"(");
		else if(key==2) strcpy(tokens[pos++],")");
		else if(key==3) strcpy(tokens[pos++],",");
		else if(key==17) strcpy(tokens[pos++],".");
		else if(key==16) strcpy(tokens[pos++],"DQUOTES");

	
	// storing the tokens complete
	if(key==14){
	strcpy(tokens[pos],"\0");
	total=pos;

		if(Lex_Error==1){
			printf("Lexical error detected\n");
			continue;
		}
		//extract the present command being parsed.
		int l=0;
		for(int i=strt;input[i]!=';' && input[i]!='\0';i++)
			present[l++]=input[i];
		present[l]='\0';

		//else continue with the syntactical analysis
		if(total!=0){
			printf("\n The list of tokens made are:\n");
			for(int i=0;i<total;i++)
				printf("%s\n",tokens[i]);
			
			pos=0;
			tree init("");
			//call for syntactical analysis HERE////////////////
/*
-----------------------------------------------------------------SYNTAX ANALYSIS FUNCTION CALLED-------------------------------------------------------------------------------
*/
			if(start(init))			////// HERE CALLING THE START SYMBOL//////////////
			{
				

				if(pos==total)   ///////IF THE RD PARSER TERURN TRUE AND STRING IS ALSO FINISHED UPTO ";" THEN ONLY THE STRING IS ACCEPTED///////////////
				{
				printf("The string is accepted\n");	
				cout<<"The parse tree: \n";
				cout<<std::string(60,' ');
				init.getVal();
				cout<<"->0";
				cout<<endl;
				std::vector<tree> q;
				/*
				TO PRINT TH PARSE TREE FOLLOWING FUNCTIONS ARE CALLED
				*/
				init.addToQ(q);
				init.showAllStatus(q);
				}
				else
				{	cout<<present;
					/////// IF POSSIBLE SYNTAX ERROR
					syntaxError(present);
				}							
			}
			else{
				cout<<present;
				syntaxError(present);}
		}
		clean_buffer();
		Lex_Error=0;
		fl=0;
		strt=posn;

	}

}



if(fl==1 && !fll)
{
flag=0;
	for(int i=0;i<62;i++){
		changecase(token,str);
		if(strcmp(keywords[i],str)==0){
			strcpy(tokens[pos],keywords[i]);
			pos++;
			flag=1;
			break;	
		}
	}


	if(flag!=1 && strcmp(token,"")!=0){
		ID_check=checkID(token);	
		if(ID_check==1 || ID_check==4)
			strcpy(tokens[pos++],"INTVAL");
		else if(ID_check==3)
			strcpy(tokens[pos++],"STRING");
		else
			Lex_Error=1;
	}

	//store the special characters in the tokens too:
	if(key<=9 && key>=4)
		strcpy(tokens[pos++],"COMPARATOR");
	else if(key==10) strcpy(tokens[pos++],"-");
	else if(key==11) strcpy(tokens[pos++],"+");
	else if(key==12) strcpy(tokens[pos++],"*");
	else if(key==13) strcpy(tokens[pos++],"/");
	else if(key==1) strcpy(tokens[pos++],"(");
	else if(key==2) strcpy(tokens[pos++],")");
	else if(key==3) strcpy(tokens[pos++],",");


strcpy(tokens[pos],"\0");
total=pos;
	int l=0;
	for(int i=strt;input[i]!=';' && input[i]!='\0';i++)
		present[l++]=input[i];
	present[l]='\0';



	if(Lex_Error==1){
		printf("Lexical error detected\n");
		return ;
	}

	cout<<present;
	cout<<std::string(l,' ')<<"^"<<endl;
	cout<<std::string(l,' ')<<";  missing here"<<endl;
}


}



/*
The main function runs an infinite while loop each instance waiting for a string, once provided the string will be parser and subsequent actions will be taken........
*/

int main(){
	printf("\n Parser started. Type 'exit' to terminate...\n");	
	char input[500];
	int flag=1;
	while(1){	
		fgets (input,500 , stdin);	
		// first we need to split the lines into multiple commands	
		if(strcmp(input,"exit\n")==0){
			printf("Goodbye :) \n");
			break;
		}	
		
		if(strcmp(input,"\n")==0)
			continue;
		parseline(input);
		
	}
	return 0;
}


/*
------------------------------------------------------------------CODE FOR SYNTAX ANALYSIS------------------------------------------------------------------------------------------------------------------
*/

/*
The epsilon transition always returns true without moving the position pointer(pos)
*/
bool epsilon_transition(tree &t)
{
	t.setVal("epsilon_transition");
	return true;
}




/*
................................................PRODUCTIONS FOR LINE OR START STATE..........................................
*/
/*
THE PRODUCTIONS HANDLED IN THE FOLLOWING CODE SNIPPET
MULTIPLE QUERIES IN SINGLE LINE

START ---> CREATE_STATEMENT LINE_PRIME | SELECT_STATEMENT LINE_PRIME | INSERT_STATEMENT LINE_PRIME | UPDATE_STATEMENT LINE_PRIME | DELETE_STATEMENT LINE_PRIME | DROP_TABLE LINE_PRIME | ALTER_TABLE LINE_PRIME

LINE_PRIME ---> CREATE_STATEMENT LINE_PRIME | SELECT_STATEMENT LINE_PRIME | INSERT_STATEMENT LINE_PRIME | UPDATE_STATEMENT LINE_PRIME | DELETE_STATEMENT LINE_PRIME | DROP_TABLE LINE_PRIME | ALTER_TABLE LINE_PRIME | EPSILON_TRANSITION;
*/

/*
 Basic structure of each function contains an input tree that comes from the parent and new tree children are created inside. if the NON-TERMINAL returns true i.e. if l1 is true then all child nodes are added
 to the parent node when recusrion unfolds.
*/

 /*
	FOR CREATE TABLE
 */
bool l1(tree &t){
	tree t1("");
	tree t2("");
	if(create_table(t1) && l_prime(t2))
	{
		t.setVal("l1");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

/*
	FOR SELECT STATEMENT
*/
bool l2(tree &t){
	tree t1("");
	tree t2("");
	
	if(select_statement(t1) && l_prime(t2)){

		t.setVal("l2");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}

	return 0;
	
}

/*
	FOR INSERT STATEMENT
*/

bool l3(tree &t){
	tree t1("");
	tree t2("");
	if(insert_statement(t1) && l_prime(t2)){
		t.setVal("l3");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

/*
	FOR UPDATE STATEMENT
*/
bool l4(tree &t){
	tree t1("");
	tree t2("");
	if(update_statement(t1) && l_prime(t2)){
		t.setVal("l4");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}
/*
	FOR DELETE STATEMENT
*/
bool l5(tree &t){
	tree t1("");
	tree t2("");
	if(delete_statement(t1) && l_prime(t2)){
		t.setVal("l5");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}
/*
	FOR DROP TABLE
*/
bool l6(tree &t){
	tree t1("");
	tree t2("");
	if(drop_table(t1) && l_prime(t2)){
		t.setVal("l6");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}
/*
	FOR ALTER TABLE
*/
bool l7(tree &t){
	tree t1("");
	tree t2("");
	if(alter_table(t1) && l_prime(t2)){
		t.setVal("l7");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

/*
START is the start symbol from where the parsing starts
*/
bool start(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=l1(t1),t.setVal("select"),t.addChild(t1),retBool(i))||
	(pos=save,i=l2(t1),t.setVal("start"),t.addChild(t1),retBool(i))||
	(pos=save,i=l3(t1),t.setVal("start"),t.addChild(t1),retBool(i))||
	(pos=save,i=l4(t1),t.setVal("start"),t.addChild(t1),retBool(i))||
	(pos=save,i=l5(t1),t.setVal("start"),t.addChild(t1),retBool(i))||
	(pos=save,i=l6(t1),t.setVal("start"),t.addChild(t1),retBool(i))||
	(pos=save,i=l7(t1),t.setVal("start"),t.addChild(t1),retBool(i));
}

/*
...........................................PRODUCTIONS FOR LINE_PRIME...........................................................................
*/

bool l_prime1(tree &t){
	tree t1(""),t2("");
	if(create_table(t1) && l_prime(t2)){
		t.setVal("l_prime1");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
	
}

bool l_prime2(tree &t){
	tree t1(""),t2("");
	if(select_statement(t1) && l_prime(t2)){
		t.setVal("l_prime2");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool l_prime3(tree &t){
	tree t1(""),t2("");
	if(insert_statement(t1) && l_prime(t2)){
		t.setVal("l_prime3");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool l_prime4(tree &t){	
	tree t1(""),t2("");
	if(update_statement(t1) && l_prime(t2)){
		t.setVal("l_prime4");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool l_prime5(tree &t){
	tree t1(""),t2("");
	if(delete_statement(t1) && l_prime(t2)){
		t.setVal("l_prime5");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool l_prime6(tree &t){
	tree t1(""),t2("");
	if(drop_table(t1) && l_prime(t2)){
		t.setVal("l_prime6");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool l_prime7(tree &t){
	tree t1(""),t2("");
	if(alter_table(t1) && l_prime(t2)){
		t.setVal("l_prime7");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}
/*
THE WRAPPER FUNCTION CALLING ALL ITS MEMBERS ONE BY ONE
*/
bool l_prime(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=l_prime1(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=l_prime2(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=l_prime3(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=l_prime4(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=l_prime5(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=l_prime6(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=l_prime7(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i)) ||
	 (pos=save,i=epsilon_transition(t1),t.setVal("l_prime"),t.addChild(t1),retBool(i));
}


/*
............................................................Create Table queries will be handled here............................................................
START----> CREATE TABLE s (element1,element2);
*/
bool  create_table(tree &t){
	tree t1(""),t2("");
	if(term("CREATE") && term("TABLE") && element(t1) && term("(") && table_element_list(t2) && term(")")){
		t.setVal("create_table");
		t.addLeaf("CREATE");
		t.addLeaf("TABLE");
		t.addChild(t1);
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

//.......................................GENERATES a string of comma seperated table elements like elem1,elem2,elem3....................................................
//												Prime functions are created to remove left recursion 
bool table_element_list(tree &t){
	tree t1(""),t2("");
	if(table_element(t1) && table_element_list_prime(t2)){
		t.setVal("table_element_list");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_element_list_prime1(tree &t){
	tree t1(""),t2("");
	if(term(",") && table_element(t1) && table_element_list_prime(t2)){
		t.setVal("table_element_list_prime1");
		t.addLeaf(",");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}


bool table_element_list_prime(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=table_element_list_prime1(t1),t.setVal("table_element_list_prime"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=epsilon_transition(t1),t.setVal("table_element_list_prime"),t.addChild(t1),retBool(i));
}



/*
.................................... THE NON TERMINAL TO PRODUCE elem1 primary key(x,y) | elem1 foreign key(abc) REFERENCE x type of productions............................................
*/
bool table_element1(tree &t){
	tree t1(""),t2(""),t3("");
	if(element(t1) && element_type(t2) && element_constraint(t3)){
		t.setVal("table_element1");
		t.addChild(t1);
		t.addChild(t2);
		t.addChild(t3);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_element2(tree &t){
	tree t1("");
	if(table_constraint(t1)){
		t.setVal("table_element2");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_element(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=table_element1(t1),t.setVal("table_element"),t.addChild(t1),retBool(i))||
	(pos=save,i=table_element2(t1),t.setVal("table_element"),t.addChild(t1),retBool(i));
}


/*
...................................... PRODCTIONS FOR PRIMARY KEY | FOREIGN KEY | UNIQUE | NOT NULLX type strings....................................................
*/
bool table_constraint1(tree &t){
	tree t1("");
	if(term("PRIMARY") && term("KEY") && term("(") && element_list(t1) && term(")")){
		t.setVal("table_element1");
		t.addLeaf("PRIMARY");
		t.addLeaf("KEY");
		t.addLeaf("(");
		t.addChild(t1);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_constraint2(tree &t){
	tree t1(""),t2("");
	if(term("FOREIGN") && term("KEY") && term("(") && element_list(t1) && term(")") && term("REFERENCES") && element(t2)){
		t.setVal("table_constraint2");
		t.addLeaf("FOREIGN");
		t.addLeaf("KEY");
		t.addLeaf("(");
		t.addChild(t1);
		t.addLeaf(")");
		t.addLeaf("REFERENCES");
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_constraint3(tree &t){
	tree t1("");
	if(term("UNIQUE") && term("(") && element_list(t1) && term(")")){
		t.setVal("table_constraint3");
		t.addLeaf("UNIQUE");
		t.addLeaf("(");
		t.addChild(t1);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_constraint4(tree &t){
	if(term("NOT") && term("NULLX")){
		t.setVal("table_constraint4");
		t.addLeaf("NOT");
		t.addLeaf("NULLX");
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool table_constraint(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=table_constraint1(t1),t.setVal("table_constraint"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=table_constraint2(t1),t.setVal("table_constraint"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=table_constraint3(t1),t.setVal("table_constraint"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=table_constraint4(t1),t.setVal("table_constraint"),t.addChild(t1),retBool(i));
}


/*
.................................................THE FOLLOWING IS THE SYNTAX FOR SELECT STATEMENT HANDLING....................................................................
SELECT_STATEMENT ---> SELECT DISTINCT_OR_NOT ELEMENT CLAUSE
*/
bool select_statement(tree &t){
	tree t1(""),t2(""),t3("");
	if(term("SELECT") && distinct_or_not(t1) && elements(t2) && clause(t3)){
		t.setVal("select_statement");
		t.addLeaf("SELECT");
		t.addChild(t1);
		t.addChild(t2);
		t.addChild(t3);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}



//productions  for terminal : distinct_or_not

// DISTINCT_OR_NOT --> DISTINCT | ALL | EPSILON_TRANSITION
bool distinct_or_not1(tree &t){
	if(term("ALL")){
		t.setVal("distinct_or_not1");
		t.addLeaf("ALL");
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool distinct_or_not2(tree &t){
	if(term("DISTINCT")){
		t.setVal("distinct_or_not2");
		t.addLeaf("DISTINCT");
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool distinct_or_not(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=distinct_or_not1(t1),t.setVal("distinct_or_not"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=distinct_or_not2(t1),t.setVal("distinct_or_not"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=epsilon_transition(t1),t.setVal("distinct_or_not"),t.addChild(t1),retBool(i));
}

//productions  for terminal : from_select
/*
CLAUSE ----> FROM ELEMENT1 AS THIS , ELEMENT2 AS THAT IF_WHERE; 
*/
bool from_select(tree &t){
	tree t1("");
	tree t2("");
	if(element(t1) && Z(t2)){
		t.setVal("from_select");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}
/*
								Z Z1 AND Z2 ARE PRODUCTIONS to make the grammar left factored and to generate long paterns of string of pattern explained above.
*/
bool Z1(tree &t){
	tree t1(""),t2("");
	if(term("AS") && element(t1) && from_select_prime(t2)){
		t.setVal("Z1");
		t.addLeaf("AS");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool Z2(tree &t){
	tree t1("");
	if(from_select_prime(t1)){
		t.setVal("Z2");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool Z(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=Z1(t1),t.setVal("Z"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=Z2(t1),t.setVal("Z"),t.addChild(t1),retBool(i));
}


bool from_select_prime1(tree &t){
	tree t1(""),t2("");
	if(term(",") && element(t1) && Z(t2)){
		t.setVal("from_select_prime1");
		t.addLeaf(",");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool from_select_prime(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=from_select_prime1(t1),t.setVal("from_select_prime"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=epsilon_transition(t1),t.setVal("from_select_prime"),t.addChild(t1),retBool(i));
}



//productions  for terminal :clause
bool clause(tree &t){
	tree t1(""),t2("");
	if(term("FROM") && from_select(t1) && if_where_to_find(t2)){
		t.setVal("clause");
		t.addLeaf("FROM");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}


/*
																		WHERE CLAUSE IS OPTIONAL and so 
																IF_WHERE ---> WHERE_CLAUSE | EPSILON_TRANSITION
*/
//productions  for terminal :if_where_to_find
bool if_where_to_find1(tree &t){
	tree t1("");
	if(term("WHERE") && where_to_find(t1)){
		t.setVal("if_where_to_find1");
		t.addLeaf("WHERE");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool if_where_to_find(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=if_where_to_find1(t1),t.setVal("if_where_to_find"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=epsilon_transition(t1),t.setVal("if_where_to_find"),t.addChild(t1),retBool(i));
}

/*
THE FOLLOWING PRODUCTIONS HANDLE MULTIPLE WAYS OF WRITING WHERE CONDITION AND ALSO HANDLES NESTED SELECT
*/
//productions  for terminal :where_to_find()
bool where_to_find1(tree &t){
	tree t1(""),t2("");
	if(term("NOT") && where_to_find(t1) && where_to_find_prime(t2)){
		t.setVal("where_to_find1");
		t.addLeaf("NOT");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool where_to_find2(tree &t){
	tree t1(""),t2("");
	if(term("(") && where_to_find(t1) && term(")") && where_to_find_prime(t2)){
		t.setVal("where_to_find2");
		t.addLeaf("(");
		t.addChild(t1);
		t.addLeaf(")");
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool where_to_find3(tree &t){
	tree t1(""),t2("");
	if(in_condition(t1) && where_to_find_prime(t2)){
		t.setVal("where_to_find3");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool where_to_find(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=where_to_find1(t1),t.setVal("where_to_find"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=where_to_find2(t1),t.setVal("where_to_find"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=where_to_find3(t1),t.setVal("where_to_find"),t.addChild(t1),retBool(i));
}


bool where_to_find_prime1(tree &t){
	tree t1(""),t2("");
	if(term("OR") && where_to_find(t1) && where_to_find_prime(t2)){
		t.setVal("where_to_find_prime1");
		t.addLeaf("OR");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}

bool where_to_find_prime2(tree &t){
	tree t1(""),t2("");
	if(term("AND") && where_to_find(t1) && where_to_find_prime(t2)){
		t.setVal("where_to_find_prime2");
		t.addLeaf("AND");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return 1;
	}
	return 0;
}
/*
A COMBINATION OF ALL SUCH SYNTAX GIVES US THE VERSITALITY OF WHERE CLAUSE
*/
bool where_to_find_prime(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=where_to_find_prime1(t1),t.setVal("where_to_find_prime"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=where_to_find_prime2(t1),t.setVal("where_to_find_prime"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=epsilon_transition(t1),t.setVal("where_to_find_prime"),t.addChild(t1),retBool(i));
}


//productions  for terminal :in_condition
/*
	THE IN_CONDITION ALSO IS A COMBINATION OF 6 PRODUCTIONS HANDLING ALL IN (SELECT_STATEMENT) | NOT IN | IN (AXT,BXT) ETC...
*/
bool in_condition1(tree &t){
	tree t1("");
	tree t2("");
	if(select_unit(t1) && term("IN") && term("(") && element_list(t2) && term(")"))
	{
		t.setVal("in_condition1");
		t.addChild(t1);
		t.addLeaf("IN");
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool in_condition2(tree &t){
	tree t1("");
	tree t2("");
	if(select_unit(t1) && term("NOT") && term("IN") && term("(") && element_list(t2) && term(")"))
	{
		t.setVal("in_condition2");
		t.addChild(t1);
		t.addLeaf("NOT");
		t.addLeaf("IN");
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool in_condition3(tree &t){
	tree t1("");
	tree t2("");
	if(select_unit(t1) && term("IN") && term("(") && select_statement(t2) && term(")"))
	{
		t.setVal("in_condition3");
		t.addChild(t1);
		t.addLeaf("IN");
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool in_condition4(tree &t){
	tree t1("");
	tree t2("");
	if(select_unit(t1) && term("NOT") && term("IN") && term("(") && select_statement(t2) && term(")"))
	{

		t.setVal("in_condition4");
		t.addChild(t1);
		t.addLeaf("NOT");
		t.addLeaf("IN");
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool in_condition5(tree &t){
	tree t1("");
	tree t2("");
	if(select_unit(t1) && term("COMPARATOR") && select_unit(t2))
	{
		t.setVal("in_condition5");
		t.addChild(t1);
		t.addLeaf("COMPARATOR");
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool in_condition6(tree &t){
	tree t1("");
	tree t2("");
	if(select_unit(t1) && term("COMPARATOR") && term("(") && select_statement(t2) && term(")"))
	{
		t.setVal("in_condition6");
		t.addChild(t1);
		t.addLeaf("COMPARATOR");
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}
/*
																WRAPPER FUNCTION OF IN_CONDITION
*/
bool in_condition(tree &t){
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=in_condition1(t1),t.setVal("in_condition"),t.addChild(t1),i ) || (pos=save,i=in_condition2(t1),t.setVal("in_condition"),t.addChild(t1),retBool(i)) || (pos=save,i=in_condition3(t1),t.setVal("in_condition"),t.addChild(t1),retBool(i)) || (pos=save,i=in_condition4(t1),t.setVal("in_condition"),t.addChild(t1),retBool(i)) || (pos=save,i=in_condition5(t1),t.setVal("in_condition"),t.addChild(t1),retBool(i)) || (pos=save,i=in_condition6(t1),t.setVal("in_condition"),t.addChild(t1),retBool(i));
}


/*
									SELECT_UNIT HANDLES THE MATHEMATICAL ASPECT OF WHERE_CLAUSE....
								HANDLES THE PRECEDENCE OF * OVER + BY MAKING * APPEAR DEEP IN PARSE TREE
													THE GRAMMAR IS UNAMBIGUIOS
*/
bool select_unit(tree &t)
{
	tree t1("");
	tree t2("");
	if(T(t1) && select_unit_prime(t2))
	{
		t.setVal("select_unit");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}


bool select_unit_prime1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("+") && T(t1) && select_unit_prime(t2))
	{
		t.setVal("select_unit_prime1");
		t.addLeaf("+");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool select_unit_prime2(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("-") && T(t1) && select_unit_prime(t2))
	{
		t.setVal("select_unit_prime2");
		t.addLeaf("-");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

/*
WRAPPER FUNCTION OF SELECT_UNIT_PRIME
*/
bool select_unit_prime(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=select_unit_prime1(t1),t.setVal("select_unit_prime"),t.addChild(t1),retBool(i)) || (pos=save,i=select_unit_prime2(t1),t.setVal("select_unit_prime"),t.addChild(t1),retBool(i)) || (pos=save,i=epsilon_transition(t1),t.setVal("select_unit_prime"),t.addChild(t1),retBool(i));
}

/*
...............................................................FUNCTIONS T AND F ARE MADE TO MAKE GRAMMAR UNAMBIGUOUS..................................................................
*/
bool T(tree &t)
{
	tree t1("");
	tree t2("");
	if(F(t1) && T_prime(t2))
	{
		t.setVal("T");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}


bool T_prime1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("*") && F(t1) && T_prime(t2))
	{
		t.setVal("T_prime1");
		t.addLeaf("*");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}


bool T_prime2(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("/") && F(t1) && T_prime(t2))
	{
		t.setVal("T_prime2");
		t.addLeaf("/");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool T_prime(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=T_prime1(t1),t.setVal("T_prime"),t.addChild(t1),retBool(i)) || (pos=save,i=T_prime2(t1),t.setVal("T_prime"),t.addChild(t1),retBool(i)) || (pos=save,i=epsilon_transition(t1),t.setVal("T_prime"),t.addChild(t1),retBool(i));
}

bool F1(tree &t)
{
	tree t1("");
	if(element(t1))
	{
		t.setVal("F1");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool F2(tree &t)
{
	if(term("INTVAL"))
	{
		t.setVal("F2");
		t.addLeaf("INTVAL");
	}
}

bool F3(tree &t)
{
	tree t1("");
	if(term("(") && select_unit(t1) && term(")"))
	{
		t.setVal("F3");
		t.addLeaf("(");
		t.addChild(t1);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool F(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=F1(t1),t.setVal("F"),t.addChild(t1),retBool(i)) || (pos=save,i=F2(t1),t.setVal("F"),t.addChild(t1),retBool(i)) || (pos=save,i=F3(t1),t.setVal("F"),t.addChild(t1),retBool(i));
}



/*
ELEMENTS HANDLE " * " IN SELECT AND HENCE IS DIFFERENT THEN ELEMENT........................................................
ELEMENTS--> *|ELEMENT,ELEMENT....
*/

// productions for terminal: elements
bool elements1(tree &t)
{
	tree t1("");
	if(term("*") && elements_prime(t1))
	{
		t.setVal("elements1");
		t.addLeaf("*");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool elements2(tree &t)
{
	tree t1("");
	tree t2("");
	if(element(t1) && X(t2))
	{
		t.setVal("elements2");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}


bool elements(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=elements1(t1),t.setVal("elements"),t.addChild(t1),retBool(i)) ||
	(pos=save,i=elements2(t1),t.setVal("elements"),t.addChild(t1),retBool(i));
}
/*
----------------------------------------------------------------HANDLES THE "." BASED REFERENCING SCHEME OF SQL----------------------------------------------------------------------------- 
*/
bool X1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term(".") && element(t1) && elements_prime(t2))
	{
		t.setVal("X1");
		t.addLeaf(".");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool X2(tree &t)
{
	tree t1("");
	if(elements_prime(t1))
	{
		t.setVal("X2");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}


bool X(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=X1(t1),t.setVal("X"),t.addChild(t1),retBool(i)) || (pos=save,i=X2(t1),t.setVal("X"),t.addChild(t1),retBool(i));
}


bool elements_prime1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term(",") && element(t1) && X(t2))
	{
		t.setVal("elements_prime1");
		t.addLeaf(",");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool elements_prime(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i= elements_prime1(t1),t.setVal("elements_prime"), t.addChild(t1),retBool(i)) || (pos=save,i=epsilon_transition(t1),t.setVal("elements_prime"), t.addChild(t1),retBool(i));
}


/*
------------------------------------------------------------PRODUCTION TO GET A LIST OF STRINGS TO PASS MULTIPLE PARAMETERS AT A TIME-------------------------------------------------
*/

bool element_list(tree &t)
{
	tree t1("");
	tree t2("");
	if(element(t1) && element_list_prime(t2))
	{
		t.setVal("element_list");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_list_prime1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term(",") && element(t1) && element_list_prime(t2))
	{
		t.setVal("element_list_prime1");
		t.addLeaf(",");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_list_prime(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i= element_list_prime1(t1),t.setVal("element_list_prime"),t.addChild(t1),retBool(i)) || (pos=save,i=epsilon_transition(t1),t.setVal("element_list_prime"),t.addChild(t1),retBool(i));
}


/*
-----------------------------------------------------------------PRODUCTION FOR CONSTRAINS ON ELEMENT(STRING)------------------------------------------------------------
																PRIMARY KEY | FOREIGN KEY | UNIQUE | NOT NULLX are some constraints
*/
bool element_constraint1(tree &t)
{
	if(term("NOT") && term("NULLX"))
	{
		t.setVal("element_constraint1");
		t.addLeaf("NOT");
		t.addLeaf("NULLX");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_constraint2(tree &t)
{
	if(term("PRIMARY") && term("KEY"))
	{
		t.setVal("element_constraint2");
		t.addLeaf("PRIMARY");
		t.addLeaf("KEY");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;	
}

bool element_constraint3(tree &t)
{
	if(term("UNIQUE"))
	{
		t.setVal("element_constraint3");
		t.addLeaf("UNIQUE");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_constraint4(tree &t)
{
	if(term("DEFAULT") && term("NULLX"))
	{
		t.setVal("element_constraint4");
		t.addLeaf("DEFAULT");
		t.addLeaf("NULLX");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

/*
WRAPPER FUNCTION OF THE CONSTRAINTS
*/
bool element_constraint(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=element_constraint1(t1),t.setVal("element_constraint"),t.addChild(t1),retBool(i)) || (pos=save,i=element_constraint2(t1),t.setVal("element_constraint"),t.addChild(t1),retBool(i)) || (pos=save,i=element_constraint3(t1),t.setVal("element_constraint"),t.addChild(t1),retBool(i)) || (pos=save,i=element_constraint4(t1),t.setVal("element_constraint"),t.addChild(t1),retBool(i)) || (pos=save,i=epsilon_transition(t1),t.setVal("element_constraint"),t.addChild(t1),retBool(i));
}






// productions for terminal: element

/*
										FOR THE PRODUCTION ELEMENT ----> STRING
*/
bool element(tree &t)
{

	if(term("STRING"))
	{
		t.setVal("element");
		t.addLeaf("STRING");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}



// productions for terminal: element_type
/*
THE FOLLOWING SERIES OF PRODUCTIONS HANDLE THE TYPE OF ELEMENTS LIKE      ELEMENT_TYPE ------>  INT | CHAR(INTVAL) | DECIMAL | VARCHAR(INTVAL)
*/
bool element_type1(tree &t)
{
	if(term("INT"))
	{
		t.setVal("element_type1");
		t.addLeaf("INT");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_type2(tree &t)
{
	if(term("CHAR") && term("(") && term("INTVAL") && term(")"))
	{

		t.setVal("element_type2");
		t.addLeaf("CHAR");
		t.addLeaf("(");
		t.addLeaf("INTVAL");
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_type3(tree &t)
{
	if(term("DECIMAL") && term("(") && term("INTVAL") && term(")"))
	{

		t.setVal("element_type3");
		t.addLeaf("DECIMAL");
		t.addLeaf("(");
		t.addLeaf("INTVAL");
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_type4(tree &t)
{
	if(term("VARCHAR") && term("(") && term("INTVAL") && term(")"))
	{
		t.setVal("element_type4");
		t.addLeaf("VARCHAR");
		t.addLeaf("(");
		t.addLeaf("INTVAL");
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool element_type(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=element_type1(t1),t.setVal("element_type"),t.addChild(t1),retBool(i)) || (pos=save,i=element_type2(t1),t.setVal("element_type"),t.addChild(t1),retBool(i)) || (pos=save,i=element_type3(t1),t.setVal("element_type"),t.addChild(t1),retBool(i)) || (pos=save,i=element_type4(t1),t.setVal("element_type"),t.addChild(t1),retBool(i));
}

/*
-------------------------------------------------------------------PRODUCTION FOR INSERT_STATEMENT QUERIES IN SQL--------------------------------------------------------------
															INSERT_STATEMENT ---> INSERT INTO TAB VALUES (element_list);
*/
bool insert_statement1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("INSERT") && term("INTO") && table_name(t1) && term("VALUES") && term("(") && element_list(t2) && term(")"))
	{
		t.setVal("insert_statement1");
		t.addLeaf("INSERT");
		t.addLeaf("INTO");
		t.addChild(t1);
		t.addLeaf("VALUES");
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool insert_statement2(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("INSERT") && term("INTO") && table_name(t1) && select_statement(t2))
	{
		t.setVal("insert_statement2");
		t.addLeaf("INSERT");
		t.addLeaf("INTO");
		t.addChild(t1);
		cout << "here I am";
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool insert_statement3(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("INSERT") && term("INTO") && table_name(t1) && term("(") && select_statement(t2) && term(")"))
	{
		t.setVal("insert_statement3");
		t.addLeaf("INSERT");
		t.addLeaf("INTO");
		t.addChild(t1);
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

bool insert_statement(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=insert_statement1(t1),t.setVal("insert_statement"),t.addChild(t1),retBool(i)) || (pos=save,i=insert_statement2(t1),t.setVal("insert_statement"),t.addChild(t1),retBool(i)) || (pos=save,i=insert_statement3(t1),t.setVal("insert_statement"),t.addChild(t1),retBool(i));
}



// productions for terminal: table_name
/*
	PRODUCTION	TABLE_NAME ---> ELEMENT;
*/
bool table_name1(tree &t)
{
	tree t1("");

	if(element(t1))
	{
		t.setVal("table_name1");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}
/*
	TABLE_NAME ----> ELEMENT(ELEMENT_LIST);
*/
bool table_name2(tree &t)
{
	tree t1("");
	tree t2("");
	if(element(t1) && term("(") && element_list(t2) && term(")"))
	{
		t.setVal("table_name2");
		t.addChild(t1);
		t.addLeaf("(");
		t.addChild(t2);
		t.addLeaf(")");
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
	{
		return false;	
	}
}

bool table_name(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=table_name1(t1),t.setVal("table_name"),t.addChild(t1),retBool(i)) || (pos=save,i=table_name2(t1),t.setVal("table_name"),t.addChild(t1),retBool(i));
}


/*
--------------------------------------------------PRODUCTION FOR UPDATE_STATEMENT QUERIES IN SQL-------------------------------------------------------------------------

*/
bool update_statement(tree &t)
{
	tree t1("");
	tree t2("");
	tree t3("");
	if(term("UPDATE") && element(t1) && term("SET") && column_values(t2) && if_where_to_find(t3))
	{
		t.setVal("update_statement");
		t.addLeaf("UPDATE");
		t.addChild(t1);
		t.addLeaf("SET");
		t.addChild(t2);
		t.addChild(t3);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}

/*
	THE COLUMN VALUES ARE NECESSARY FOR UPDATE STATEMENT HAVING A DIFFERENT SYNTAX ALL TOGETHER
*/
bool column_values(tree &t)
{
	tree t1("");
	tree t2("");
	tree t3("");
	if(element(t1) && term("COMPARATOR") && term("DQUOTES") && element(t2) && term("DQUOTES") && column_values_prime(t3))
	{
		t.setVal("column_values");
		t.addChild(t1);
		t.addLeaf("COMPARATOR");
		t.addLeaf("DQUOTES");
		t.addChild(t2);
		t.addLeaf("DQUOTES");
		t.addChild(t3);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
	{
		return false;
	}
}

bool column_values_prime1(tree &t)
{
	tree t1("");
	tree t2("");
	tree t3("");
	if(term(",") && element(t1) && term("COMPARATOR") && term("DQUOTES") && element(t2) && term("DQUOTES") && column_values_prime(t3))
	{
		t.setVal("column_values_prime1");
		t.addLeaf(",");
		t.addChild(t1);
		t.addLeaf("COMPARATOR");
		t.addLeaf("DQUOTES");
		t.addChild(t2);
		t.addLeaf("DQUOTES");
		t.addChild(t3);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
	{
		return false;
	}
}

bool column_values_prime(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=column_values_prime1(t1),t.setVal("column_values_prime"),t.addChild(t1),retBool(i)) || (pos=save,i=epsilon_transition(t1),t.setVal("column_values_prime"),t.addChild(t1),retBool(i));
}

/*
-----------------------------------------------------------------------------------PRODUCTIONS FOR DELETE STATEMENT---------------------------------------------------------------------------
																			DELETE_STATEMENT --> DELETE FROM STRING IF_WHERE;
*/
bool delete_statement(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("DELETE") && term("FROM") && element(t1) && if_where_to_find(t2))
	{
		t.setVal("delete_statement");
		t.addLeaf("DELETE");
		t.addLeaf("FROM");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
		return false;
}

/*
----------------------------------------------------------------------------------PRODUCTIONS FROM DROP TABLE------------------------------------------------------------------------------
																				DROP_TABLE---> DROP TABLE TAB_NAME;
*/
bool drop_table(tree &t)
{	
	tree t1("");
	if(term("DROP") && term("TABLE") && element(t1)){
		t.setVal("drop_table");
		t.addLeaf("DROP");
		t.addLeaf("TABLE");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	return false;
}



/*
-----------------------------------------------------------------------------------PRODUCTIONS FOR ALTER TABLE----------------------------------------------------------------
*/
bool alter_table(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("ALTER") && term("TABLE") && element(t1) && Y(t2))
	{
		t.setVal("alter_table");
		t.addLeaf("ALTER");
		t.addLeaf("TABLE");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
		return false;
}

/*
THE function Y is required to remove left recursion from our grammar of alter table whixh handles ADD or DROP COLUMN syntax necessary for alter table........
*/

bool Y1(tree &t)
{
	tree t1("");
	tree t2("");
	if(term("ADD") && element(t1) && element_type(t2))
	{
		t.setVal("Y1");
		t.addLeaf("ADD");
		t.addChild(t1);
		t.addChild(t2);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
		return false;
}

bool Y2(tree &t)
{
	tree t1("");
	if(term("DROP") && term("COLUMN") && element(t1))
	{
		t.setVal("Y2");
		t.addLeaf("DROP");
		t.addLeaf("COLUMN");
		t.addChild(t1);
		if(maxparse<pos)
			maxparse=pos;
		return true;
	}
	else
		return false;
}
/*
WRAPPER FUNCTION OF Y
*/
bool Y(tree &t)
{
	int save=pos;
	tree t1("");
	bool i=false;
	return (pos=save,i=Y1(t1),t.setVal("Y"),t.addChild(t1),retBool(i)) || (pos=save,i=Y2(t1),t.setVal("Y"),t.addChild(t1),retBool(i));
}

/*
----------------------------------------------------------------------------------SYNTAX ANALYSIS ENDS------------------------------------------------------------------------------
*/

/*
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------THANK YOU-------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/