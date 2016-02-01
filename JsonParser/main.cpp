#include"json.h"
#include<time.h>

FILE* fp;


int main(){

	const char* filename = "E:\\test.json";
	const char* out = "E:\\out.json";


	if ((fp = fopen(filename, "r")) ==NULL){
		printf("fail opne file\n");
		exit(-1);
	}

	char *val = (char*)malloc(204800);
	int size=fread(val, 1, 204800, fp);
	*(val + size) = '\0';

	clock_t start = clock();
	jsonValue *tree = jsonParse(val);
	clock_t end = clock();
	int d = end - start;
	printf("%d\n",d);


	
//   jsonValue* json = createNode(ObjectK);
 //   jsonValue* arr = createNode(ArrayK);
 //   addMember(json, "Array", arr);
 //   addIntMember(json, "Int", 10);
 //   addDoubleMember(json, "Double", 12.23);
 //   addBooleanMember(json, "Boolean", 0);
 //   addBooleanMember(json, "True", 1);
 //   addNullMember(json, "Null");
 //   addStringMember(json, "Fuck", "fuck you assholes");
 //   jsonValue* arr2 = hasMember(json, "Array");
 //   if (arr != NULL){
	//addIntItem(arr, 10);
	//jsonValue* ob = createNode(ObjectK);
	//addIntMember(ob, "haah", 12);
	//addStringMember(ob, "History", "historyer");
	//addIntItem(arr, 12);
	//addStringItem(arr, "fuck you asshole");
	//addItem(arr,ob);
 //   }
	//printJson(tree,0);

	return 0;
}