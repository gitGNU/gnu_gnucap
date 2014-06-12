/*$Id: interp.cc,v 26.133 2014/07/05 18:30:00
 * Copyright (C) 2013 Rishabh Yadav
 * Author: Rishabh Yadav <rishabh.ece.iitbhu@gmail.com>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------*/
//A basic interpreter
/*TO DO..
1.Integrate into gnucap.
2.Functionalities:
-->Expression Evaluation(WIP)
-->Detect comment and int & string variable (DONE)
-->Conditionals

Methods to be implemented
1.init():Load all the necessary variables as soon as the interpreter initialises
2.get_token():reads the source code and returns the next symbol(token) from the script/source code parser
3.eval_token():depending on the type of token,call the appropriate method.
4.eval_exp(): Evaluate the expression and return the result.
5.update_env():Updates the variable values and environment variables.
*
*===================================================================================
Environment variables(lives durnig the execution of the program)
1.prog_buf:points to the start of program buffer
2.prog:points to current location in source code.
3.variable[]:array used to store the variables in scope during the execution of the program
4.tokens
5.token_type
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "interpreter.h" //Library

#define NUM_VARIABLE 80
#define NAME_LENGTH 20
#define VALUE_LENGTH 20
#define TOKEN_SIZE 80
#define PROG_SIZE 10000

char *prog;
char *prog_buf;


enum tok_type {DELIMITER, IDENTIFIER, NUMBER, KEYWORD, TEMP,STRING, BLOCK};
enum tokens_var {ARG, CHAR, INT, IF, ELSE, FOR, DO, WHILE, SWITCH,RETURN, EOL, FINISHED, END};
char tok,token_type;
char token[80];

typedef struct variable_structure{
	char type;
	char name[NAME_LENGTH];
	char value[VALUE_LENGTH];	
}variable[NUM_VARIABLE];


int load(char *p, char *fname);
int get_token(void);
int isdelim(char c), look_up(char *s), iswhite(char c);


int main(int argc,char* argv[]){
	if(argc!=2){
		printf("Usage: gnucap <filename.gp>\n");
		exit(1);
	}
	 /* Memory allocation for the program */
	printf("allocating memory for the program.....\n");
  if((prog_buf=(char *) malloc(PROG_SIZE))==NULL) {
    printf("allocation failure");
    exit(1);
  }
	printf("allocation successfull.\nloading the program...");
	if(!load(prog_buf,argv[1]))
		exit(1);
	printf("loaded....\nInitialise the interpreter\n");
	//init();Not much needed at this level but it needs to be implemented.
	
	//printf("prog_buf:%c\n",*prog_buf);//For Debugging.
	prog = prog_buf;//Game starts from here...
	//To be Continued....
	//Depending of the token_type returned by get_token() call appropriate function.


	return 0;	
}




/* Load a program. */
int load(char *p, char *fname)
{
  FILE *fp;
  if((fp=fopen(fname, "rb"))==NULL) return 0;
  int i = 0;
  do {
    *p = getc(fp);
   	 p++;
		 i++;
  }while(!feof(fp) && i<PROG_SIZE);

  *(p-2) = '\0'; /* null terminate the program */
  fclose(fp);
  return 1;
}


int get_token(void){
	//Get the symbol and interpret its type/nature and maintain(increment/whatever) the "prog" variable.
	//Ignore white space
  register char *temp;
  token_type = 0; tok = 0;
  temp = token;
  *temp = '\0';
	while(iswhite(*prog) && *prog) ++prog; 
  if(*prog=='\r') { 
    ++prog; 
    ++prog;
    /* skip over white space */
    while(iswhite(*prog) && *prog) ++prog;
  }
	if(*prog=='\0') { /* end of file */
    *token = '\0';
    tok = FINISHED;
    return(token_type=DELIMITER);
  }
	  /* look for comments */
  if(*prog=='/')
    if(*(prog+1)=='*') { /* is a comment */
      prog += 2;
      printf("Comment detected\n");
      do { /* find end of comment */
        while(*prog!='*') prog++;
        
        prog++;
        printf("%c\n",*prog);
      } while (*prog!='/');
      printf("%c\n",*prog);
      prog++;
      printf("%c\n",*prog);
    }
	if(*prog=='"') { /* quoted string */
    prog++;
    while(*prog!='"'&& *prog!='\r') *temp++ = *prog++;
    if(*prog=='\r'){ 
			printf("Syntax Error\n");
			exit(1);
		}
    prog++; *temp = '\0';
    return(token_type=STRING);
  }
  if(isdigit(*prog)) { /* number */
    while(!isdelim(*prog)) *temp++ = *prog++;
    *temp = '\0';
    return(token_type = NUMBER);
  }
  return token_type;
}


