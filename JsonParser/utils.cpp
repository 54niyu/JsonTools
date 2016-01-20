#include"utils.h"
int isInt(TreeNode* n){
	if (n){
		return n->nodekind == IntK;
	}
	return 0;
}
int isDouble(TreeNode* n){
	if (n){
		return n->nodekind == DoubleK;
	}
	return 0;
}
int isArray(TreeNode* n){
	if (n){
		return n->nodekind == ArrayK;
	}
	return 0;
}
int isObject(TreeNode* n){
	if (n){
		return n->nodekind == ObjectK;
	}
	return 0;
}
int isBool(TreeNode* n){
	if (n){
		return n->nodekind == BooleanK;
	}
	return 0;
}
int isNull(TreeNode* n){
	if (n){
		return n->nodekind == NullK;
	}
}

TreeNode* hasMember(TreeNode* n, const char *key){
	if (!n&&n->nodekind == ObjectK){
		TreeNode* ptr = n->child;
		while (ptr){
			if (strcmp(ptr->val.stringVal, key)){
				return ptr->child;
			}
		}
	}
	return nullptr;
}
int addMember(TreeNode* n, const char *key){

}
void printJson(TreeNode* root,int tab){
	if (root != nullptr){

		switch (root->nodekind){
		case ArrayK:{
			for (int i = 0; i < tab; i++)
				printf(" ");
			printf("[\n");
			TreeNode* ptr = root->child;
			while (ptr != nullptr){
				printJson(ptr,tab+2);
				printf(",\n");
				ptr = ptr->subling;
			}
			for (int i = 0; i < tab; i++)
				printf(" ");
			printf("]");
		}; break;
		case ObjectK:{
			for (int i = 0; i < tab; i++)
				printf(" ");
			printf("{\n");
			TreeNode* ptr = root->child;
			while (ptr != nullptr){
				printJson(ptr,tab+2);
				printf(",\n");
				ptr = ptr->subling;
			}
			for (int i = 0; i < tab; i++)
				printf(" ");
			printf("}");
		}; break;
		case KeyK:{
			for (int i = 0; i < tab; i++)
				printf(" ");
			printf("\"%s\":", root->val.stringVal);
			printJson(root->child,tab+2);
		}; break;
		case IntK:{
			printf("%d", root->val.intVal);
		}; break;
		case DoubleK:{
			printf("%lf", root->val.doubleVal);
		}; break;
		case BooleanK:{
			printf("%s", root->val.intVal == 0 ? "false": "true");
		}; break;
		case NullK:{
			printf("null");
		}; break;
		case StringK:{
			printf("\"%s\"", root->val.stringVal);
		}; break;
		default:printf("Something is Wrong");
		}
	}
}