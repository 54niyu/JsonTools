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

TreeNode* hasMember(TreeNode* n, const char *key);
//
int addMember(TreeNode* n, const char *key);

void printJson(TreeNode* r,int tab);

#endif