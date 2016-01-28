#include"json.h"

//generate api
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
	return 0;
}

void setInt(TreeNode* n){
    n->nodekind = IntK;
}
void setDouble(TreeNode* n){
    n->nodekind = DoubleK;
}
void setArray(TreeNode* n){
    n->nodekind = ArrayK;
}
void setObject(TreeNode* n){
    n->nodekind = ObjectK;
}
void setBool(TreeNode* n){
    n->nodekind = BooleanK;
}
void setNull(TreeNode* n){
    n->nodekind = NullK;
}

//for Object
TreeNode* hasMember(TreeNode* n, const char *key){
	if (n&&n->nodekind == ObjectK){
		TreeNode* ptr = n->child;
		while (ptr){
			if (strcmp(ptr->val.stringVal, key)){
				return ptr->child;
			}
			ptr = ptr->subling;
		}
	}
	return nullptr;
}
int addMember(TreeNode* n, const char *key, TreeNode* value){
    if (n&&n->nodekind == ObjectK){
	auto ptr = n->child;
	if (ptr == nullptr){
	    TreeNode* k= createNode(KeyK);
	    k->val.stringVal = (char*)malloc(strlen(key) + 1);
	    strcpy(k->val.stringVal, key);
	    n->child = k;
	    k->child = value;
	    return 1;
	}
	else{
	    do{
		if (strcmp(ptr->val.stringVal, key) == 0)
		    return 0;
		if (ptr->subling != NULL)
		    ptr = ptr->subling;
		else
		    break;
	    } while (true);
	    TreeNode* k = createNode(KeyK);
	    k->val.stringVal = (char*)malloc(strlen(key) + 1);
	    strcpy(k->val.stringVal, key);
	    k->child = value;
	    ptr->subling = k;
	    return 1;
	}
    }
    return 0;
}
int addIntMember(TreeNode* n, const char *key,int value){
    TreeNode* temp = createNode(IntK);
    temp->val.intVal = value;
    return addMember(n, key, temp);
}
int addDoubleMember(TreeNode* n, const char* key, double value){
    TreeNode* temp = createNode(IntK);
    temp->val.doubleVal= value;
    return addMember(n, key, temp);
}
int addStringMember(TreeNode* n, const char* key, const char* value){
    TreeNode* temp = createNode(StringK);
    temp->val.stringVal = (char*)malloc(strlen(value));
    strcpy(temp->val.stringVal, value);
    return addMember(n, key, temp);
}
int addBooleanMember(TreeNode* n, const char* key, int value){
    TreeNode* temp = createNode(BooleanK);
    temp->val.intVal = value;
    return addMember(n, key, temp);
}
int addNullMember(TreeNode* n, const char* key){
    TreeNode* temp = createNode(NullK);
    return addMember(n, key, temp);
}

//for Array
int addItem(TreeNode* n, TreeNode* value){
    if (n&&n->nodekind ==ArrayK){
	auto ptr = n->child;
	if (ptr == nullptr){
	    n->child = value;
	    return 1;
	}
	else{
	    do{
		if (ptr->subling != NULL)
		    ptr = ptr->subling;
		else
		    break;
	    } while (true);
	    ptr->subling = value;
	    return 1;
	}
    }
    return 0;
}
int addIntItem(TreeNode* n, int value){
    TreeNode* val = createNode(IntK);
    val->val.intVal = value;
    return addItem(n, val);
}
int addDoubleItem(TreeNode* n, double value){
    TreeNode* val = createNode(DoubleK);
    val->val.doubleVal = value;
    return addItem(n, val);
}
int addStringItem(TreeNode* n, const char* value){
    TreeNode* temp = createNode(StringK);
    temp->val.stringVal = (char*)malloc(strlen(value));
    strcpy(temp->val.stringVal, value);
    return addItem(n ,temp);
}
int addBooleanItem(TreeNode* n, int value){
    TreeNode* temp = createNode(BooleanK);
    temp->val.intVal = value;
    return addItem(n,temp);
}
int addNullItem(TreeNode* n){
    TreeNode* temp = createNode(NullK);
    return addItem(n, temp);
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
		    for (int i = 0; i < tab; i++)
			printf(" ");
			printf("%d", root->val.intVal);
		}; break;
		case DoubleK:{
		    for (int i = 0; i < tab; i++)
			printf(" ");
			printf("%lf", root->val.doubleVal);
		}; break;
		case BooleanK:{
		    for (int i = 0; i < tab; i++)
			printf(" ");
			printf("%s", root->val.intVal == 0 ? "false": "true");
		}; break;
		case NullK:{
		    for (int i = 0; i < tab; i++)
			printf(" ");
			printf("null");
		}; break;
		case StringK:{
		    for (int i = 0; i < tab; i++)
			printf(" ");
			printf("\"%s\"", root->val.stringVal);
		}; break;
		default:printf("Something is Wrong");
		}
	}
}