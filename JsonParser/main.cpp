#include<stdlib.h>
#include<stdio.h>
#include"tokenier.h"
#include"parser.h"
#include"utils.h"


FILE* fp;

int main(){

	//const char* filename = "E:\\test.json";
	//const char* out = "E:\\out.json";

	//freopen(out, "w", stdout);

	//if ((fp = fopen(filename, "r")) ==nullptr){
	//	printf("fail opne file\n");
	//	exit(-1);
	//}

	//fillBuffer();

	//TreeNode *tree = JSON();

    TreeNode* json = createNode(ObjectK);
    TreeNode* arr = createNode(ArrayK);
    addMember(json, "Array", arr);
    addIntMember(json, "Int", 10);
    addDoubleMember(json, "Double", 12.23);
    addBooleanMember(json, "Boolean", 0);
    addBooleanMember(json, "True", 1);
    addNullMember(json, "Null");
	printJson(json,0);

	return 0;
}