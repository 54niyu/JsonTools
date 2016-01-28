#include"json.h"

extern Token tokenValue;
extern char* cp;
extern char* limit;

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

TreeNode* jsonParse(char* value){
    cp = value;
    limit = value + strlen(value);

    TreeNode* root = nullptr;
    getToken();
    if (tokenValue.tokenType == LCBracket){
	root = Object();
    }
    else if (tokenValue.tokenType == LQBracket){
	root = Array();
    }
    else{
	printf("invalid");
	return NULL;
    }
    return root;
}


TreeNode* Object(){
	getToken();
	TreeNode* obj = createNode(ObjectK);
	TreeNode* first = nullptr;
	while(tokenValue.tokenType != RCBracket){
		if (first == nullptr){
			first = KeyValue();
			obj->child = first;
		}
		else{
			first->subling = KeyValue();
			first = first->subling;
		}
		if (tokenValue.tokenType == Comma){
			getToken();
		}
		else {
		    break;
		}
	}

	if (tokenValue.tokenType == RCBracket){
		getToken();
	}
	else{
		printf("Object error");
		return NULL;
	}

	return obj;
}
TreeNode* KeyValue(){
	TreeNode* key = createNode(KeyK);
	if (tokenValue.tokenType == String){
		key->val.stringVal = tokenValue.attribute.stringVal;
		getToken();
	}
	else{
		printf("Key error");
		return NULL;
	}
	if (tokenValue.tokenType == Colon){
		getToken();
	}
	else{
		printf("Colon error");
		return NULL;
	}
	key->child = Value();
	return key;
}
TreeNode* Array(){
	getToken();
	TreeNode* ary = createNode(ArrayK);
	TreeNode*  first = nullptr;
	while (tokenValue.tokenType != RQBracket){
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
		if (tokenValue.tokenType == Comma){
			getToken();
		}
		else{
		    break;
		}
	}
	if (tokenValue.tokenType == RQBracket){
		getToken();
	}
	else{
		printf("Array error");
		return NULL;
	}
	return ary;
}
TreeNode* Value(){
	TreeNode* value = nullptr;
	switch (tokenValue.tokenType){
	case LCBracket:{value = Object(); }; break;
	case LQBracket:{value = Array(); }; break;
	case String:{value = createNode(StringK); value->val.stringVal = tokenValue.attribute.stringVal; getToken(); }; break;
	case Int:{value = createNode(IntK); value->val.intVal = tokenValue.attribute.intVal; getToken(); }; break;
	case Double:{value = createNode(DoubleK); value->val.doubleVal = tokenValue.attribute.doubleVal; getToken();; }; break;
	case True:{value = createNode(BooleanK); value->val.intVal = 1; getToken(); }; break;
	case False:{value = createNode(BooleanK); value->val.intVal = 0; getToken(); }; break;
	case Null:{value = createNode(NullK); getToken(); }; break;
	default:{printf("not valid value\n"); return NULL; };
	}
	return value;
}