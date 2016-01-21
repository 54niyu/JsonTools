#ifndef _TOKENIER_
#define _TOKENIER_
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
typedef enum{
	//structural chararcters
	LQBracket, RQBracket, LCBracket, RCBracket, Colon, Comma,
	//values
	Int, Double,
	String,
	//literal names
	True, False, Null,
} TokenType;

typedef struct{
	TokenType tokenType;
	union {
		int intVal;
		double doubleVal;
		char* stringVal;
	} attribute;
} Token;
void getToken();
void fillBuffer();
#endif