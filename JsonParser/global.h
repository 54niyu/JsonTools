#ifndef _GLOBAL_H_
#define _GLOBAL_H_

//tokenier.h
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

//parser.h
typedef enum { ArrayK, ObjectK, KeyK, StringK, IntK, DoubleK, BooleanK, NullK } nodeKind;

typedef struct treeNode{
    struct treeNode* child;
    struct treeNode* subling;
    nodeKind nodekind;
    union {
	char* stringVal;
	int intVal;
	double doubleVal;
    } val;
} TreeNode;
#endif