#include"json.h"

extern Token tokenValue;
extern char* cp;
extern char* limit;

jsonValue* Object();
jsonValue* KeyValue();
jsonValue* Array();
jsonValue* ArrayValue();
jsonValue* Value();
jsonValue* Number();
jsonValue* createNode2(nodeKind kind){
	jsonValue* root = (jsonValue*)malloc(sizeof(jsonValue));
	root->child = NULL;
	root->subling = NULL;
	root->nodekind = kind;
	return  root;
}

jsonValue* jsonParse(char* value){
    cp = value;
    limit = value + strlen(value);

    jsonValue* root = NULL;
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
jsonValue* Object(){
	getToken();
	jsonValue* obj = createNode(ObjectK);
	jsonValue* first = NULL;
	while(tokenValue.tokenType != RCBracket){
		if (first == NULL){
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
jsonValue* KeyValue(){
	jsonValue* key = createNode(KeyK);
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
jsonValue* Array(){
	getToken();
	jsonValue* ary = createNode(ArrayK);
	jsonValue*  first = NULL;
	while (tokenValue.tokenType != RQBracket){
		if (first == NULL){
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
jsonValue* Value(){
	jsonValue* value = NULL;
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