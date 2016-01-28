#ifndef _JSON_H_
#define _JSON_H_
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>


//tokenier
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
//tokenier end

//parser
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
TreeNode* JSON();
TreeNode* createNode(nodeKind kind);
//parser end

//utils
int isInt(TreeNode* n);
int isDouble(TreeNode* n);
int isArray(TreeNode* n);
int isObject(TreeNode* n);
int isBool(TreeNode* n);
int isNull(TreeNode* n);
void setInt(TreeNode* n);
void setDouble(TreeNode* n);
void setArray(TreeNode* n);
void setObject(TreeNode* n);
void setBool(TreeNode* n);
void setNull(TreeNode* n);
//for Object
TreeNode* hasMember(TreeNode* n, const char *key);
int addMember(TreeNode* n, const char *key, TreeNode* value);
int addIntMember(TreeNode* n, const char *key, int value);
int addDoubleMember(TreeNode* n, const char* key, double value);
int addStringMember(TreeNode* n, const char* key, const char* value);
int addBooleanMember(TreeNode* n, const char* key, int value);
int addNullMember(TreeNode* n, const char* key);
//for Array
int addItem(TreeNode* n, TreeNode* value);
int addIntItem(TreeNode* n, int value);
int addDoubleItem(TreeNode* n, double value);
int addStringItem(TreeNode* n, const char* value);
int addBooleanItem(TreeNode* n, int value);
int addNullItem(TreeNode* n);

void printJson(TreeNode* r, int tab);
//utils  end

//encode
int utf8ToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf8(unsigned char* dist, unsigned* src, size_t size);
int utf16leToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf16le(unsigned char* dist, unsigned* src, size_t size);
int utf16beToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf16be(unsigned char* dist, unsigned* src, size_t size);
int utf32leToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf32le(unsigned char* dist, unsigned* src, size_t size);
int utf32beToCp(unsigned* dist, unsigned char* src, size_t size);
int cpToUtf32be(unsigned char* dist, unsigned* src, size_t size);
//encode end
#endif