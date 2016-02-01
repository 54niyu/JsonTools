#include"json.h"

//generate api
int isInt(jsonValue* n){
	if (n){
		return n->nodekind == IntK;
	}
	return 0;
}
int isDouble(jsonValue* n){
	if (n){
		return n->nodekind == DoubleK;
	}
	return 0;
}
int isArray(jsonValue* n){
	if (n){
		return n->nodekind == ArrayK;
	}
	return 0;
}
int isObject(jsonValue* n){
	if (n){
		return n->nodekind == ObjectK;
	}
	return 0;
}
int isBool(jsonValue* n){
	if (n){
		return n->nodekind == BooleanK;
	}
	return 0;
}
int isNull(jsonValue* n){
	if (n){
		return n->nodekind == NullK;
	}
	return 0;
}

void setInt(jsonValue* n){
    n->nodekind = IntK;
}
void setDouble(jsonValue* n){
    n->nodekind = DoubleK;
}
void setArray(jsonValue* n){
    n->nodekind = ArrayK;
}
void setObject(jsonValue* n){
    n->nodekind = ObjectK;
}
void setBool(jsonValue* n){
    n->nodekind = BooleanK;
}
void setNull(jsonValue* n){
    n->nodekind = NullK;
}

//for Object
jsonValue* hasMember(jsonValue* n, const char *key){
	if (n&&n->nodekind == ObjectK){
		jsonValue* ptr = n->child;
		while (ptr){
			if (strcmp(ptr->val.stringVal, key)){
				return ptr->child;
			}
			ptr = ptr->subling;
		}
	}
	return NULL;
}
int addMember(jsonValue* n, const char *key, jsonValue* value){
    if (n&&n->nodekind == ObjectK){
	auto ptr = n->child;
	if (ptr == NULL){
	    jsonValue* k= createNode(KeyK);
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
	    jsonValue* k = createNode(KeyK);
	    k->val.stringVal = (char*)malloc(strlen(key) + 1);
	    strcpy(k->val.stringVal, key);
	    k->child = value;
	    ptr->subling = k;
	    return 1;
	}
    }
    return 0;
}
int addIntMember(jsonValue* n, const char *key,int value){
    jsonValue* temp = createNode(IntK);
    temp->val.intVal = value;
    return addMember(n, key, temp);
}
int addDoubleMember(jsonValue* n, const char* key, double value){
    jsonValue* temp = createNode(IntK);
    temp->val.doubleVal= value;
    return addMember(n, key, temp);
}
int addStringMember(jsonValue* n, const char* key, const char* value){
    jsonValue* temp = createNode(StringK);
    temp->val.stringVal = (char*)malloc(strlen(value));
    strcpy(temp->val.stringVal, value);
    return addMember(n, key, temp);
}
int addBooleanMember(jsonValue* n, const char* key, int value){
    jsonValue* temp = createNode(BooleanK);
    temp->val.intVal = value;
    return addMember(n, key, temp);
}
int addNullMember(jsonValue* n, const char* key){
    jsonValue* temp = createNode(NullK);
    return addMember(n, key, temp);
}

//for Array
int addItem(jsonValue* n, jsonValue* value){
    if (n&&n->nodekind ==ArrayK){
	auto ptr = n->child;
	if (ptr == NULL){
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
int addIntItem(jsonValue* n, int value){
    jsonValue* val = createNode(IntK);
    val->val.intVal = value;
    return addItem(n, val);
}
int addDoubleItem(jsonValue* n, double value){
    jsonValue* val = createNode(DoubleK);
    val->val.doubleVal = value;
    return addItem(n, val);
}
int addStringItem(jsonValue* n, const char* value){
    jsonValue* temp = createNode(StringK);
    temp->val.stringVal = (char*)malloc(strlen(value));
    strcpy(temp->val.stringVal, value);
    return addItem(n ,temp);
}
int addBooleanItem(jsonValue* n, int value){
    jsonValue* temp = createNode(BooleanK);
    temp->val.intVal = value;
    return addItem(n,temp);
}
int addNullItem(jsonValue* n){
    jsonValue* temp = createNode(NullK);
    return addItem(n, temp);
}

void printJson(jsonValue* root,int tab){
	if (root != NULL){

		switch (root->nodekind){
		case ArrayK:{
			for (int i = 0; i < tab; i++)
				printf(" ");
			printf("[\n");
			jsonValue* ptr = root->child;
			while (ptr != NULL){
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
			jsonValue* ptr = root->child;
			while (ptr != NULL){
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