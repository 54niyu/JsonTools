#ifndef _PARSER_
#define _PARSER_

typedef enum {ArrayK,ObjectK,KeyK,StringK,IntK,DoubleK,BooleanK,NullK} nodeKind;

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

TreeNode* JSON();
TreeNode* createNode(nodeKind kind);
#endif