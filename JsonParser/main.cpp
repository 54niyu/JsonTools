#include"json.h"
#include<wchar.h>
FILE* fp;

int main(){

    //��������
	const char* filename = "E:\\test.json";
	const char* out = "E:\\out.json";

	freopen(out, "w", stdout);

	if ((fp = fopen(filename, "r")) ==nullptr){
		printf("fail opne file\n");
		exit(-1);
	}

	fillBuffer();

	TreeNode *tree = JSON();

 //   TreeNode* json = createNode(ObjectK);
 //   TreeNode* arr = createNode(ArrayK);
 //   addMember(json, "Array", arr);
 //   addIntMember(json, "Int", 10);
 //   addDoubleMember(json, "Double", 12.23);
 //   addBooleanMember(json, "Boolean", 0);
 //   addBooleanMember(json, "True", 1);
 //   addNullMember(json, "Null");
 //   addStringMember(json, "Fuck", "fuck you assholes");
 //   TreeNode* arr2 = hasMember(json, "Array");
 //   if (arr != NULL){
	//addIntItem(arr, 10);
	//TreeNode* ob = createNode(ObjectK);
	//addIntMember(ob, "haah", 12);
	//addStringMember(ob, "History", "historyer");
	//addIntItem(arr, 12);
	//addStringItem(arr, "fuck you asshole");
	//addItem(arr,ob);
 //   }
	printJson(tree,0);

	return 0;
}