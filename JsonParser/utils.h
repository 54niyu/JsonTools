#ifndef _UTILS_H_
#define _UTILS_H_
#include"tokenier.h"
#include"parser.h"

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
#endif