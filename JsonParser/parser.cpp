#include"parser.h"
#include"tokenier.h"
#include<stdlib.h>

extern Token tokenStream[1024];
int index = 0;

TreeNode* Object();
TreeNode* KeyValue();
TreeNode* Array();
TreeNode* ArrayValue();
TreeNode* Value();
TreeNode* Number();

TreeNode* createNode(nodeKind kind){
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->child = nullptr;
	root->subling = nullptr;
	root->nodekind = kind;
	return  root;
}
TreeNode* JSON(){

	TreeNode* root = nullptr;

	if (tokenStream[index].tokenType == LCBracket){
		root = Object();
	}
	else if (tokenStream[index].tokenType == LQBracket){
		root = Array();
	}
	else{
		printf("invalid");
//		exit(0);
	}
	return root;
}
TreeNode* Object(){
	index++;
	TreeNode* obj = createNode(ObjectK);
	TreeNode* first = nullptr;
	while(tokenStream[index].tokenType != RCBracket){
		if (first == nullptr){
			first = KeyValue();
			obj->child = first;
		}
		else{
			first->subling = KeyValue();
			first = first->subling;
		}
		if (tokenStream[index].tokenType == Comma){
			index++;
		}
		else {
			break;
		}
	}

	if (tokenStream[index].tokenType == RCBracket){
		index++;
	}
	else{
		printf("Object error");
//		exit(0);
	}

	return obj;
}
TreeNode* KeyValue(){
	TreeNode* key = createNode(KeyK);
	if (tokenStream[index].tokenType == String){
		key->val.stringVal = tokenStream[index++].attribute.stringVal;
	}
	else{
		printf("Key error");
	}
	if (tokenStream[index].tokenType == Colon){
		index++;
	}
	else{
		printf("Colon error");
	}
	key->child = Value();
	return key;
}
TreeNode* Array(){
	index++;
	TreeNode* ary = createNode(ArrayK);
	TreeNode*  first = nullptr;
	while (tokenStream[index].tokenType != RQBracket){
		if (first == nullptr){
			first = Value();
			ary->child = first;
			ary->val.intVal = 1;
		}
		else{
			first->subling = Value();
			first = first->subling;
			ary->val.intVal++;
		}
		if (tokenStream[index].tokenType == Comma){
			index++;
		}
		else{
			break;
		}
	}
	if (tokenStream[index].tokenType == RQBracket){
		index++;
	}
	else{
		printf("Array error");
	}
	return ary;
}
TreeNode* Value(){
	TreeNode* value = nullptr;
	switch (tokenStream[index].tokenType){
	case LCBracket:{value = Object(); }; break;
	case LQBracket:{value = Array(); }; break;
	case String:{value = createNode(StringK); value->val.stringVal = tokenStream[index].attribute.stringVal; index++; }; break;
	case Int:{value = createNode(IntK); value->val.intVal = tokenStream[index].attribute.intVal; index++; }; break;
	case Double:{value = createNode(DoubleK); value->val.doubleVal = tokenStream[index].attribute.doubleVal; index++;; }; break;
	case True:{value = createNode(BooleanK); value->val.intVal = 1; index++; }; break;
	case False:{value = createNode(BooleanK); value->val.intVal = 0; index++; }; break;
	case Null:{value = createNode(NullK); index++; }; break;
	}
	return value;
}