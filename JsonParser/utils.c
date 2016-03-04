#include"json.h"

//for Object
jsonValue* hasMember(jsonValue* n, const char *key){
	if (n&&n->nodekind == ObjectK){
		jsonValue* ptr = n->child;
		while (ptr){
			if (strcmp(ptr->val.stringVal, key)==0){
				return ptr->child;
			}
			ptr = ptr->subling;
		}
	}
	return NULL;
}
int addMember(jsonValue* n, const char *key, jsonValue* value){
    if (n&&n->nodekind == ObjectK){
	jsonValue* ptr = n->child;
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
	    } while (1);
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
    jsonValue* temp = createNode(DoubleK);
    temp->val.doubleVal= value;
    return addMember(n, key, temp);
}
int addStringMember(jsonValue* n, const char* key, const char* value){
    jsonValue* temp = createNode(StringK);
    temp->val.stringVal = (char*)malloc(strlen(value)+1);
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
	jsonValue* ptr = n->child;
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
	    } while (1);
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
    temp->val.stringVal = (char*)malloc(strlen(value)+1);
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

int getArrarySize(jsonValue* n){
    if (n->nodekind != ArrayK)
	return 0;
    if (n->child == NULL)
	return 0;
    jsonValue* ptr = n->child;
    int size = 1;
    while (ptr->subling != NULL){
	ptr = ptr->subling;
	size++;
    }
    return size;
}
jsonValue* getElement(jsonValue* arr, int index){
    if (arr->nodekind != ArrayK)
	return NULL;
    jsonValue* ptr = arr->child;
    while (index >0&&ptr!=NULL){
	ptr = ptr->subling;
	index--;
    }
    return ptr;
}
void removeElement(jsonValue* arr, int index){
    if (arr->nodekind != ArrayK){
	return;
    }
    //add head node
    jsonValue* head = createNode(ArrayK);
    head->subling = arr->child;
    jsonValue* ptr = head;
    while (index&&ptr->subling != NULL){
	index--;
	ptr = ptr->subling;
    }
    //delete element at index
    jsonValue* temp = ptr->subling;
    ptr->subling = ptr->subling->subling;
    deleteValue(temp);

    //delete head node
    arr->child = head->subling;
    free(head);
}
void removeMember(jsonValue* obj, char* key){
    if (obj == NULL || obj->nodekind != ObjectK)
	return;

    jsonValue	*head = createNode(0), *ptr = NULL;
    head->subling = obj->child;
    ptr = head;

    while (ptr->subling != NULL){
	if (strcmp(ptr->subling->val.stringVal, key)==0){
	    break;
	}
	else{
	    ptr = ptr->subling;
	}
    }

    jsonValue* temp = ptr->subling;
    ptr->subling = ptr->subling->subling;

    deleteValue(temp);

    obj->child = head->subling;
    free(head);
}
void deleteValue(jsonValue* value){
    if (value != NULL){
	switch (value->nodekind){
	case ArrayK:
	case ObjectK:{
	    jsonValue* ptr = value->child;
	    while (ptr != NULL){
		jsonValue* temp = ptr;
		ptr = ptr->subling;
		deleteValue(temp);
	    }
	}; break;
	case KeyK:{
	    //free Value
	    deleteValue(value->child);
	    //free Key Name
	    free(value->val.stringVal);
	    //free Key
	    free(value);
	}; break;
	case IntK:
	case DoubleK:
	case BooleanK:
	case NullK:{
	    free(value);
	}; break;
	case StringK:{
	    free(value->val.stringVal);
	    free(value);
	}; break;
	}
    }
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